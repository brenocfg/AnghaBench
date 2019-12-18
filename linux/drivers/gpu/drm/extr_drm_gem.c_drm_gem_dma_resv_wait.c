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
typedef  int /*<<< orphan*/  u32 ;
struct drm_gem_object {int /*<<< orphan*/  resv; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 long EINVAL ; 
 long ETIME ; 
 long dma_resv_wait_timeout_rcu (int /*<<< orphan*/ ,int,int,unsigned long) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 

long drm_gem_dma_resv_wait(struct drm_file *filep, u32 handle,
				    bool wait_all, unsigned long timeout)
{
	long ret;
	struct drm_gem_object *obj;

	obj = drm_gem_object_lookup(filep, handle);
	if (!obj) {
		DRM_DEBUG("Failed to look up GEM BO %d\n", handle);
		return -EINVAL;
	}

	ret = dma_resv_wait_timeout_rcu(obj->resv, wait_all,
						  true, timeout);
	if (ret == 0)
		ret = -ETIME;
	else if (ret > 0)
		ret = 0;

	drm_gem_object_put_unlocked(obj);

	return ret;
}