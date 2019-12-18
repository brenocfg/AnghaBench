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
struct vkms_gem_object {int /*<<< orphan*/  vaddr; } ;
struct vkms_composer {int /*<<< orphan*/  fb; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  blend (void*,int /*<<< orphan*/ ,struct vkms_composer*,struct vkms_composer*) ; 
 struct drm_gem_object* drm_gem_fb_get_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vkms_gem_object* drm_gem_to_vkms_gem (struct drm_gem_object*) ; 

__attribute__((used)) static void compose_cursor(struct vkms_composer *cursor_composer,
			   struct vkms_composer *primary_composer,
			   void *vaddr_out)
{
	struct drm_gem_object *cursor_obj;
	struct vkms_gem_object *cursor_vkms_obj;

	cursor_obj = drm_gem_fb_get_obj(&cursor_composer->fb, 0);
	cursor_vkms_obj = drm_gem_to_vkms_gem(cursor_obj);

	if (WARN_ON(!cursor_vkms_obj->vaddr))
		return;

	blend(vaddr_out, cursor_vkms_obj->vaddr,
	      primary_composer, cursor_composer);
}