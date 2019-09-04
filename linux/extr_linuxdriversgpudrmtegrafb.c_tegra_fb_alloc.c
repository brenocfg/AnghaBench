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
struct tegra_bo {int /*<<< orphan*/  gem; } ;
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/ ** obj; TYPE_1__* format; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int num_planes; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_framebuffer_init (struct drm_device*,struct drm_framebuffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,struct drm_framebuffer*,struct drm_mode_fb_cmd2 const*) ; 
 int /*<<< orphan*/  kfree (struct drm_framebuffer*) ; 
 struct drm_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_fb_funcs ; 

__attribute__((used)) static struct drm_framebuffer *tegra_fb_alloc(struct drm_device *drm,
					      const struct drm_mode_fb_cmd2 *mode_cmd,
					      struct tegra_bo **planes,
					      unsigned int num_planes)
{
	struct drm_framebuffer *fb;
	unsigned int i;
	int err;

	fb = kzalloc(sizeof(*fb), GFP_KERNEL);
	if (!fb)
		return ERR_PTR(-ENOMEM);

	drm_helper_mode_fill_fb_struct(drm, fb, mode_cmd);

	for (i = 0; i < fb->format->num_planes; i++)
		fb->obj[i] = &planes[i]->gem;

	err = drm_framebuffer_init(drm, fb, &tegra_fb_funcs);
	if (err < 0) {
		dev_err(drm->dev, "failed to initialize framebuffer: %d\n",
			err);
		kfree(fb);
		return ERR_PTR(err);
	}

	return fb;
}