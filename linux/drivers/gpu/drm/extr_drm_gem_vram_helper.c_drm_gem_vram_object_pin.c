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
struct drm_gem_vram_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct drm_gem_vram_object* drm_gem_vram_of_gem (struct drm_gem_object*) ; 
 int drm_gem_vram_pin (struct drm_gem_vram_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_gem_vram_object_pin(struct drm_gem_object *gem)
{
	struct drm_gem_vram_object *gbo = drm_gem_vram_of_gem(gem);

	/* Fbdev console emulation is the use case of these PRIME
	 * helpers. This may involve updating a hardware buffer from
	 * a shadow FB. We pin the buffer to it's current location
	 * (either video RAM or system memory) to prevent it from
	 * being relocated during the update operation. If you require
	 * the buffer to be pinned to VRAM, implement a callback that
	 * sets the flags accordingly.
	 */
	return drm_gem_vram_pin(gbo, 0);
}