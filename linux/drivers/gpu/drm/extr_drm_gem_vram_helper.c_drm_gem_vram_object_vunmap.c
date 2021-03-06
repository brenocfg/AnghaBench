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
 int /*<<< orphan*/  drm_gem_vram_kunmap (struct drm_gem_vram_object*) ; 
 struct drm_gem_vram_object* drm_gem_vram_of_gem (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_vram_unpin (struct drm_gem_vram_object*) ; 

__attribute__((used)) static void drm_gem_vram_object_vunmap(struct drm_gem_object *gem,
				       void *vaddr)
{
	struct drm_gem_vram_object *gbo = drm_gem_vram_of_gem(gem);

	drm_gem_vram_kunmap(gbo);
	drm_gem_vram_unpin(gbo);
}