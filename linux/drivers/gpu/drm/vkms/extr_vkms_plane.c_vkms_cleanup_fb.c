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
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
struct drm_plane {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct drm_gem_object* drm_gem_fb_get_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkms_gem_vunmap (struct drm_gem_object*) ; 

__attribute__((used)) static void vkms_cleanup_fb(struct drm_plane *plane,
			    struct drm_plane_state *old_state)
{
	struct drm_gem_object *gem_obj;

	if (!old_state->fb)
		return;

	gem_obj = drm_gem_fb_get_obj(old_state->fb, 0);
	vkms_gem_vunmap(gem_obj);
}