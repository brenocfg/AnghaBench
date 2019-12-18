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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct vkms_gem_object {TYPE_1__ gem; int /*<<< orphan*/  vaddr; } ;
struct drm_framebuffer {int dummy; } ;
struct vkms_composer {struct drm_framebuffer fb; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  compose_cursor (struct vkms_composer*,struct vkms_composer*,void*) ; 
 int /*<<< orphan*/  compute_crc (void*,struct vkms_composer*) ; 
 struct drm_gem_object* drm_gem_fb_get_obj (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 struct vkms_gem_object* drm_gem_to_vkms_gem (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t _vkms_get_crc(struct vkms_composer *primary_composer,
			      struct vkms_composer *cursor_composer)
{
	struct drm_framebuffer *fb = &primary_composer->fb;
	struct drm_gem_object *gem_obj = drm_gem_fb_get_obj(fb, 0);
	struct vkms_gem_object *vkms_obj = drm_gem_to_vkms_gem(gem_obj);
	void *vaddr_out = kzalloc(vkms_obj->gem.size, GFP_KERNEL);
	u32 crc = 0;

	if (!vaddr_out) {
		DRM_ERROR("Failed to allocate memory for output frame.");
		return 0;
	}

	if (WARN_ON(!vkms_obj->vaddr)) {
		kfree(vaddr_out);
		return crc;
	}

	memcpy(vaddr_out, vkms_obj->vaddr, vkms_obj->gem.size);

	if (cursor_composer)
		compose_cursor(cursor_composer, primary_composer, vaddr_out);

	crc = compute_crc(vaddr_out, primary_composer);

	kfree(vaddr_out);

	return crc;
}