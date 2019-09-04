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
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ gemfs; } ;
struct drm_i915_private {TYPE_1__ mm; } ;
struct drm_gem_object {struct file* filp; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 int PTR_ERR (struct file*) ; 
 unsigned long VM_NORESERVE ; 
 int /*<<< orphan*/  drm_gem_private_object_init (struct drm_device*,struct drm_gem_object*,size_t) ; 
 struct file* shmem_file_setup (char*,size_t,unsigned long) ; 
 struct file* shmem_file_setup_with_mnt (scalar_t__,char*,size_t,unsigned long) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int i915_gem_object_create_shmem(struct drm_device *dev,
					struct drm_gem_object *obj,
					size_t size)
{
	struct drm_i915_private *i915 = to_i915(dev);
	unsigned long flags = VM_NORESERVE;
	struct file *filp;

	drm_gem_private_object_init(dev, obj, size);

	if (i915->mm.gemfs)
		filp = shmem_file_setup_with_mnt(i915->mm.gemfs, "i915", size,
						 flags);
	else
		filp = shmem_file_setup("i915", size, flags);

	if (IS_ERR(filp))
		return PTR_ERR(filp);

	obj->filp = filp;

	return 0;
}