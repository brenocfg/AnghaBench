#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct plane {scalar_t__ dma_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {TYPE_1__ base; struct drm_gem_object** obj; } ;
struct omap_framebuffer {struct plane* planes; int /*<<< orphan*/  lock; struct drm_format_info const* format; struct drm_framebuffer base; } ;
struct drm_mode_fb_cmd2 {unsigned int* pitches; unsigned int height; scalar_t__ pixel_format; unsigned int* offsets; int /*<<< orphan*/  width; } ;
struct drm_gem_object {unsigned int size; } ;
struct drm_format_info {int num_planes; unsigned int* cpp; int vsub; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  DBG (char*,struct drm_device*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_framebuffer_init (struct drm_device*,struct drm_framebuffer*,int /*<<< orphan*/ *) ; 
 struct drm_format_info* drm_get_format_info (struct drm_device*,struct drm_mode_fb_cmd2 const*) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,struct drm_framebuffer*,struct drm_mode_fb_cmd2 const*) ; 
 scalar_t__* formats ; 
 int /*<<< orphan*/  kfree (struct omap_framebuffer*) ; 
 struct omap_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_framebuffer_funcs ; 
 int omap_gem_mmap_size (struct drm_gem_object*) ; 

struct drm_framebuffer *omap_framebuffer_init(struct drm_device *dev,
		const struct drm_mode_fb_cmd2 *mode_cmd, struct drm_gem_object **bos)
{
	const struct drm_format_info *format = NULL;
	struct omap_framebuffer *omap_fb = NULL;
	struct drm_framebuffer *fb = NULL;
	unsigned int pitch = mode_cmd->pitches[0];
	int ret, i;

	DBG("create framebuffer: dev=%p, mode_cmd=%p (%dx%d@%4.4s)",
			dev, mode_cmd, mode_cmd->width, mode_cmd->height,
			(char *)&mode_cmd->pixel_format);

	format = drm_get_format_info(dev, mode_cmd);

	for (i = 0; i < ARRAY_SIZE(formats); i++) {
		if (formats[i] == mode_cmd->pixel_format)
			break;
	}

	if (!format || i == ARRAY_SIZE(formats)) {
		dev_dbg(dev->dev, "unsupported pixel format: %4.4s\n",
			(char *)&mode_cmd->pixel_format);
		ret = -EINVAL;
		goto fail;
	}

	omap_fb = kzalloc(sizeof(*omap_fb), GFP_KERNEL);
	if (!omap_fb) {
		ret = -ENOMEM;
		goto fail;
	}

	fb = &omap_fb->base;
	omap_fb->format = format;
	mutex_init(&omap_fb->lock);

	/*
	 * The code below assumes that no format use more than two planes, and
	 * that the two planes of multiplane formats need the same number of
	 * bytes per pixel.
	 */
	if (format->num_planes == 2 && pitch != mode_cmd->pitches[1]) {
		dev_dbg(dev->dev, "pitches differ between planes 0 and 1\n");
		ret = -EINVAL;
		goto fail;
	}

	if (pitch % format->cpp[0]) {
		dev_dbg(dev->dev,
			"buffer pitch (%u bytes) is not a multiple of pixel size (%u bytes)\n",
			pitch, format->cpp[0]);
		ret = -EINVAL;
		goto fail;
	}

	for (i = 0; i < format->num_planes; i++) {
		struct plane *plane = &omap_fb->planes[i];
		unsigned int vsub = i == 0 ? 1 : format->vsub;
		unsigned int size;

		size = pitch * mode_cmd->height / vsub;

		if (size > omap_gem_mmap_size(bos[i]) - mode_cmd->offsets[i]) {
			dev_dbg(dev->dev,
				"provided buffer object is too small! %zu < %d\n",
				bos[i]->size - mode_cmd->offsets[i], size);
			ret = -EINVAL;
			goto fail;
		}

		fb->obj[i]    = bos[i];
		plane->dma_addr  = 0;
	}

	drm_helper_mode_fill_fb_struct(dev, fb, mode_cmd);

	ret = drm_framebuffer_init(dev, fb, &omap_framebuffer_funcs);
	if (ret) {
		dev_err(dev->dev, "framebuffer init failed: %d\n", ret);
		goto fail;
	}

	DBG("create: FB ID: %d (%p)", fb->base.id, fb);

	return fb;

fail:
	kfree(omap_fb);

	return ERR_PTR(ret);
}