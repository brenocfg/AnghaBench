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
struct drm_framebuffer {int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 int OMAP_BO_TILED ; 
 int omap_gem_flags (int /*<<< orphan*/ ) ; 

bool omap_framebuffer_supports_rotation(struct drm_framebuffer *fb)
{
	return omap_gem_flags(fb->obj[0]) & OMAP_BO_TILED;
}