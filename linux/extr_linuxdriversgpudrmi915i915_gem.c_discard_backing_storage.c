#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* filp; } ;
struct TYPE_4__ {scalar_t__ madv; } ;
struct drm_i915_gem_object {TYPE_3__ base; TYPE_1__ mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  f_count; } ;

/* Variables and functions */
 scalar_t__ I915_MADV_WILLNEED ; 
 int atomic_long_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool discard_backing_storage(struct drm_i915_gem_object *obj)
{
	/* If we are the last user of the backing storage (be it shmemfs
	 * pages or stolen etc), we know that the pages are going to be
	 * immediately released. In this case, we can then skip copying
	 * back the contents from the GPU.
	 */

	if (obj->mm.madv != I915_MADV_WILLNEED)
		return false;

	if (obj->base.filp == NULL)
		return true;

	/* At first glance, this looks racy, but then again so would be
	 * userspace racing mmap against close. However, the first external
	 * reference to the filp can only be obtained through the
	 * i915_gem_mmap_ioctl() which safeguards us against the user
	 * acquiring such a reference whilst we are in the middle of
	 * freeing the object.
	 */
	return atomic_long_read(&obj->base.filp->f_count) == 1;
}