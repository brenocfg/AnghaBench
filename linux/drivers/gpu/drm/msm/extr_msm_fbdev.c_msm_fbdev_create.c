#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_fbdev {struct fb_info* fb; } ;
struct msm_drm_private {TYPE_1__* kms; } ;
struct TYPE_8__ {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_7__ {int /*<<< orphan*/  smem_len; void* smem_start; } ;
struct fb_info {struct drm_device* height; struct fb_info* width; TYPE_4__ var; int /*<<< orphan*/  par; TYPE_3__ fix; int /*<<< orphan*/  screen_size; struct fb_info* screen_base; int /*<<< orphan*/ * fbops; } ;
struct drm_gem_object {int /*<<< orphan*/  size; } ;
struct drm_framebuffer {struct drm_device* height; struct drm_framebuffer* width; TYPE_4__ var; int /*<<< orphan*/  par; TYPE_3__ fix; int /*<<< orphan*/  screen_size; struct drm_framebuffer* screen_base; int /*<<< orphan*/ * fbops; } ;
struct drm_fb_helper_surface_size {int /*<<< orphan*/  surface_height; int /*<<< orphan*/  surface_width; int /*<<< orphan*/  surface_bpp; int /*<<< orphan*/  fb_height; int /*<<< orphan*/  fb_width; int /*<<< orphan*/  surface_depth; } ;
struct drm_fb_helper {struct fb_info* fb; struct drm_device* dev; } ;
struct TYPE_6__ {void* fb_base; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_2__ mode_config; int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  aspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,struct fb_info*,struct drm_device*,...) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ IS_ERR (struct fb_info*) ; 
 int PTR_ERR (struct fb_info*) ; 
 int align_pitch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fb_info* drm_fb_helper_alloc_fbi (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_fb_helper_fill_info (struct fb_info*,struct drm_fb_helper*,struct drm_fb_helper_surface_size*) ; 
 int /*<<< orphan*/  drm_framebuffer_remove (struct fb_info*) ; 
 int /*<<< orphan*/  drm_mode_legacy_fb_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fb_info* msm_alloc_stolen_fb (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_fb_ops ; 
 struct drm_gem_object* msm_framebuffer_bo (struct fb_info*,int /*<<< orphan*/ ) ; 
 int msm_gem_get_and_pin_iova (struct drm_gem_object*,int /*<<< orphan*/ ,void**) ; 
 struct fb_info* msm_gem_get_vaddr (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct msm_fbdev* to_msm_fbdev (struct drm_fb_helper*) ; 

__attribute__((used)) static int msm_fbdev_create(struct drm_fb_helper *helper,
		struct drm_fb_helper_surface_size *sizes)
{
	struct msm_fbdev *fbdev = to_msm_fbdev(helper);
	struct drm_device *dev = helper->dev;
	struct msm_drm_private *priv = dev->dev_private;
	struct drm_framebuffer *fb = NULL;
	struct drm_gem_object *bo;
	struct fb_info *fbi = NULL;
	uint64_t paddr;
	uint32_t format;
	int ret, pitch;

	format = drm_mode_legacy_fb_format(sizes->surface_bpp, sizes->surface_depth);

	DBG("create fbdev: %dx%d@%d (%dx%d)", sizes->surface_width,
			sizes->surface_height, sizes->surface_bpp,
			sizes->fb_width, sizes->fb_height);

	pitch = align_pitch(sizes->surface_width, sizes->surface_bpp);
	fb = msm_alloc_stolen_fb(dev, sizes->surface_width,
			sizes->surface_height, pitch, format);

	if (IS_ERR(fb)) {
		DRM_DEV_ERROR(dev->dev, "failed to allocate fb\n");
		return PTR_ERR(fb);
	}

	bo = msm_framebuffer_bo(fb, 0);

	mutex_lock(&dev->struct_mutex);

	/*
	 * NOTE: if we can be guaranteed to be able to map buffer
	 * in panic (ie. lock-safe, etc) we could avoid pinning the
	 * buffer now:
	 */
	ret = msm_gem_get_and_pin_iova(bo, priv->kms->aspace, &paddr);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "failed to get buffer obj iova: %d\n", ret);
		goto fail_unlock;
	}

	fbi = drm_fb_helper_alloc_fbi(helper);
	if (IS_ERR(fbi)) {
		DRM_DEV_ERROR(dev->dev, "failed to allocate fb info\n");
		ret = PTR_ERR(fbi);
		goto fail_unlock;
	}

	DBG("fbi=%p, dev=%p", fbi, dev);

	fbdev->fb = fb;
	helper->fb = fb;

	fbi->fbops = &msm_fb_ops;

	drm_fb_helper_fill_info(fbi, helper, sizes);

	dev->mode_config.fb_base = paddr;

	fbi->screen_base = msm_gem_get_vaddr(bo);
	if (IS_ERR(fbi->screen_base)) {
		ret = PTR_ERR(fbi->screen_base);
		goto fail_unlock;
	}
	fbi->screen_size = bo->size;
	fbi->fix.smem_start = paddr;
	fbi->fix.smem_len = bo->size;

	DBG("par=%p, %dx%d", fbi->par, fbi->var.xres, fbi->var.yres);
	DBG("allocated %dx%d fb", fbdev->fb->width, fbdev->fb->height);

	mutex_unlock(&dev->struct_mutex);

	return 0;

fail_unlock:
	mutex_unlock(&dev->struct_mutex);
	drm_framebuffer_remove(fb);
	return ret;
}