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
struct scheduling_resources {unsigned long long queue_mask; unsigned long long gws_mask; int /*<<< orphan*/  vmid_mask; scalar_t__ gds_heap_size; scalar_t__ gds_heap_base; scalar_t__ oac_mask; } ;
struct device_queue_manager {int /*<<< orphan*/  packets; TYPE_2__* dev; } ;
struct TYPE_3__ {int num_queue_per_pipe; int num_pipe_per_mec; int /*<<< orphan*/  queue_bitmap; int /*<<< orphan*/  compute_vmid_bitmap; } ;
struct TYPE_4__ {TYPE_1__ shared_resources; } ;

/* Variables and functions */
 int KGD_MAX_QUEUES ; 
 scalar_t__ WARN_ON (int) ; 
 int pm_send_set_resources (int /*<<< orphan*/ *,struct scheduling_resources*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_sched_resources(struct device_queue_manager *dqm)
{
	int i, mec;
	struct scheduling_resources res;

	res.vmid_mask = dqm->dev->shared_resources.compute_vmid_bitmap;

	res.queue_mask = 0;
	for (i = 0; i < KGD_MAX_QUEUES; ++i) {
		mec = (i / dqm->dev->shared_resources.num_queue_per_pipe)
			/ dqm->dev->shared_resources.num_pipe_per_mec;

		if (!test_bit(i, dqm->dev->shared_resources.queue_bitmap))
			continue;

		/* only acquire queues from the first MEC */
		if (mec > 0)
			continue;

		/* This situation may be hit in the future if a new HW
		 * generation exposes more than 64 queues. If so, the
		 * definition of res.queue_mask needs updating
		 */
		if (WARN_ON(i >= (sizeof(res.queue_mask)*8))) {
			pr_err("Invalid queue enabled by amdgpu: %d\n", i);
			break;
		}

		res.queue_mask |= (1ull << i);
	}
	res.gws_mask = ~0ull;
	res.oac_mask = res.gds_heap_base = res.gds_heap_size = 0;

	pr_debug("Scheduling resources:\n"
			"vmid mask: 0x%8X\n"
			"queue mask: 0x%8llX\n",
			res.vmid_mask, res.queue_mask);

	return pm_send_set_resources(&dqm->packets, &res);
}