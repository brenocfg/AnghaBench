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
struct timespec {int dummy; } ;
struct etnaviv_gpu {int /*<<< orphan*/  fence_event; } ;
struct etnaviv_gem_object {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 long ERESTARTSYS ; 
 int ETIMEDOUT ; 
 unsigned long etnaviv_timeout_to_jiffies (struct timespec*) ; 
 int /*<<< orphan*/  is_active (struct etnaviv_gem_object*) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

int etnaviv_gpu_wait_obj_inactive(struct etnaviv_gpu *gpu,
	struct etnaviv_gem_object *etnaviv_obj, struct timespec *timeout)
{
	unsigned long remaining;
	long ret;

	if (!timeout)
		return !is_active(etnaviv_obj) ? 0 : -EBUSY;

	remaining = etnaviv_timeout_to_jiffies(timeout);

	ret = wait_event_interruptible_timeout(gpu->fence_event,
					       !is_active(etnaviv_obj),
					       remaining);
	if (ret > 0)
		return 0;
	else if (ret == -ERESTARTSYS)
		return -ERESTARTSYS;
	else
		return -ETIMEDOUT;
}