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
typedef  int uint32_t ;
struct drm_gem_object {int /*<<< orphan*/  resv; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 int MSM_PREP_NOSYNC ; 
 int MSM_PREP_WRITE ; 
 long dma_resv_wait_timeout_rcu (int /*<<< orphan*/ ,int,int,unsigned long) ; 
 unsigned long timeout_to_jiffies (int /*<<< orphan*/ *) ; 

int msm_gem_cpu_prep(struct drm_gem_object *obj, uint32_t op, ktime_t *timeout)
{
	bool write = !!(op & MSM_PREP_WRITE);
	unsigned long remain =
		op & MSM_PREP_NOSYNC ? 0 : timeout_to_jiffies(timeout);
	long ret;

	ret = dma_resv_wait_timeout_rcu(obj->resv, write,
						  true,  remain);
	if (ret == 0)
		return remain == 0 ? -EBUSY : -ETIMEDOUT;
	else if (ret < 0)
		return ret;

	/* TODO cache maintenance */

	return 0;
}