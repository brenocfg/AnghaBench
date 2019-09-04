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
struct tegra_bo {int dummy; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_fb_get_obj (struct drm_framebuffer*,unsigned int) ; 
 struct tegra_bo* to_tegra_bo (int /*<<< orphan*/ ) ; 

struct tegra_bo *tegra_fb_get_plane(struct drm_framebuffer *framebuffer,
				    unsigned int index)
{
	return to_tegra_bo(drm_gem_fb_get_obj(framebuffer, index));
}