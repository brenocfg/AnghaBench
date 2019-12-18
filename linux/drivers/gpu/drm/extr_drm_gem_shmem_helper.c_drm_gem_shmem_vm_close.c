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
struct vm_area_struct {struct drm_gem_object* vm_private_data; } ;
struct drm_gem_shmem_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_shmem_put_pages (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  drm_gem_vm_close (struct vm_area_struct*) ; 
 struct drm_gem_shmem_object* to_drm_gem_shmem_obj (struct drm_gem_object*) ; 

__attribute__((used)) static void drm_gem_shmem_vm_close(struct vm_area_struct *vma)
{
	struct drm_gem_object *obj = vma->vm_private_data;
	struct drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	drm_gem_shmem_put_pages(shmem);
	drm_gem_vm_close(vma);
}