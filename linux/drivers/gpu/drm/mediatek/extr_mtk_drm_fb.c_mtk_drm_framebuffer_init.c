#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {struct drm_gem_object** obj; } ;
struct drm_format_info {int num_planes; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int drm_framebuffer_init (struct drm_device*,struct drm_framebuffer*,int /*<<< orphan*/ *) ; 
 struct drm_format_info* drm_get_format_info (struct drm_device*,struct drm_mode_fb_cmd2 const*) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,struct drm_framebuffer*,struct drm_mode_fb_cmd2 const*) ; 
 int /*<<< orphan*/  kfree (struct drm_framebuffer*) ; 
 struct drm_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_drm_fb_funcs ; 

__attribute__((used)) static struct drm_framebuffer *mtk_drm_framebuffer_init(struct drm_device *dev,
					const struct drm_mode_fb_cmd2 *mode,
					struct drm_gem_object *obj)
{
	const struct drm_format_info *info = drm_get_format_info(dev, mode);
	struct drm_framebuffer *fb;
	int ret;

	if (info->num_planes != 1)
		return ERR_PTR(-EINVAL);

	fb = kzalloc(sizeof(*fb), GFP_KERNEL);
	if (!fb)
		return ERR_PTR(-ENOMEM);

	drm_helper_mode_fill_fb_struct(dev, fb, mode);

	fb->obj[0] = obj;

	ret = drm_framebuffer_init(dev, fb, &mtk_drm_fb_funcs);
	if (ret) {
		DRM_ERROR("failed to initialize framebuffer\n");
		kfree(fb);
		return ERR_PTR(ret);
	}

	return fb;
}