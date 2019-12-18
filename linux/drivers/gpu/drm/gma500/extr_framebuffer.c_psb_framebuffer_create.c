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
struct drm_framebuffer {int dummy; } ;
struct psb_framebuffer {struct drm_framebuffer base; } ;
struct gtt_range {int dummy; } ;
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct psb_framebuffer*) ; 
 struct psb_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int psb_framebuffer_init (struct drm_device*,struct psb_framebuffer*,struct drm_mode_fb_cmd2 const*,struct gtt_range*) ; 

__attribute__((used)) static struct drm_framebuffer *psb_framebuffer_create
			(struct drm_device *dev,
			 const struct drm_mode_fb_cmd2 *mode_cmd,
			 struct gtt_range *gt)
{
	struct psb_framebuffer *fb;
	int ret;

	fb = kzalloc(sizeof(*fb), GFP_KERNEL);
	if (!fb)
		return ERR_PTR(-ENOMEM);

	ret = psb_framebuffer_init(dev, fb, mode_cmd, gt);
	if (ret) {
		kfree(fb);
		return ERR_PTR(ret);
	}
	return &fb->base;
}