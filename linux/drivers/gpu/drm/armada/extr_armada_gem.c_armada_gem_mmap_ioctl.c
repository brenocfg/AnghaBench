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
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_armada_gem_mmap {unsigned long addr; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  filp; } ;
struct armada_gem_object {TYPE_1__ obj; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 struct armada_gem_object* armada_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (TYPE_1__*) ; 
 unsigned long vm_mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int armada_gem_mmap_ioctl(struct drm_device *dev, void *data,
	struct drm_file *file)
{
	struct drm_armada_gem_mmap *args = data;
	struct armada_gem_object *dobj;
	unsigned long addr;

	dobj = armada_gem_object_lookup(file, args->handle);
	if (dobj == NULL)
		return -ENOENT;

	if (!dobj->obj.filp) {
		drm_gem_object_put_unlocked(&dobj->obj);
		return -EINVAL;
	}

	addr = vm_mmap(dobj->obj.filp, 0, args->size, PROT_READ | PROT_WRITE,
		       MAP_SHARED, args->offset);
	drm_gem_object_put_unlocked(&dobj->obj);
	if (IS_ERR_VALUE(addr))
		return addr;

	args->addr = addr;

	return 0;
}