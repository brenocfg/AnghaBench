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
struct exynos_drm_gem {int /*<<< orphan*/  kvaddr; } ;
struct exynos_drm_fbdev {struct exynos_drm_gem* exynos_gem; } ;
struct drm_framebuffer {scalar_t__ funcs; } ;
struct drm_fb_helper {struct drm_framebuffer* fb; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  drm_framebuffer_remove (struct drm_framebuffer*) ; 
 struct exynos_drm_fbdev* to_exynos_fbdev (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_drm_fbdev_destroy(struct drm_device *dev,
				      struct drm_fb_helper *fb_helper)
{
	struct exynos_drm_fbdev *exynos_fbd = to_exynos_fbdev(fb_helper);
	struct exynos_drm_gem *exynos_gem = exynos_fbd->exynos_gem;
	struct drm_framebuffer *fb;

	vunmap(exynos_gem->kvaddr);

	/* release drm framebuffer and real buffer */
	if (fb_helper->fb && fb_helper->fb->funcs) {
		fb = fb_helper->fb;
		if (fb)
			drm_framebuffer_remove(fb);
	}

	drm_fb_helper_unregister_fbi(fb_helper);

	drm_fb_helper_fini(fb_helper);
}