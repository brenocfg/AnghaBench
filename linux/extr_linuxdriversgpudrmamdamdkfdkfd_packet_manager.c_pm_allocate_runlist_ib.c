#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct packet_manager {int allocated; int /*<<< orphan*/  lock; TYPE_2__* ib_buffer_obj; TYPE_1__* dqm; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpu_addr; void* cpu_ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int kfd_gtt_sa_allocate (int /*<<< orphan*/ ,unsigned int,TYPE_2__**) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_calc_rlib_size (struct packet_manager*,unsigned int*,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int pm_allocate_runlist_ib(struct packet_manager *pm,
				unsigned int **rl_buffer,
				uint64_t *rl_gpu_buffer,
				unsigned int *rl_buffer_size,
				bool *is_over_subscription)
{
	int retval;

	if (WARN_ON(pm->allocated))
		return -EINVAL;

	pm_calc_rlib_size(pm, rl_buffer_size, is_over_subscription);

	mutex_lock(&pm->lock);

	retval = kfd_gtt_sa_allocate(pm->dqm->dev, *rl_buffer_size,
					&pm->ib_buffer_obj);

	if (retval) {
		pr_err("Failed to allocate runlist IB\n");
		goto out;
	}

	*(void **)rl_buffer = pm->ib_buffer_obj->cpu_ptr;
	*rl_gpu_buffer = pm->ib_buffer_obj->gpu_addr;

	memset(*rl_buffer, 0, *rl_buffer_size);
	pm->allocated = true;

out:
	mutex_unlock(&pm->lock);
	return retval;
}