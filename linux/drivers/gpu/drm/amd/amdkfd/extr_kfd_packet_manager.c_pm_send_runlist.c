#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct packet_manager {int /*<<< orphan*/  lock; TYPE_3__* priv_queue; TYPE_1__* pmf; } ;
struct list_head {int dummy; } ;
struct TYPE_7__ {int (* acquire_packet_buffer ) (TYPE_3__*,size_t,int /*<<< orphan*/ **) ;int /*<<< orphan*/  (* rollback_packet ) (TYPE_3__*) ;int /*<<< orphan*/  (* submit_packet ) (TYPE_3__*) ;} ;
struct TYPE_8__ {TYPE_2__ ops; } ;
struct TYPE_6__ {int runlist_size; int (* runlist ) (struct packet_manager*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_create_runlist_ib (struct packet_manager*,struct list_head*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  pm_release_ib (struct packet_manager*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,size_t,int /*<<< orphan*/ **) ; 
 int stub2 (struct packet_manager*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 

int pm_send_runlist(struct packet_manager *pm, struct list_head *dqm_queues)
{
	uint64_t rl_gpu_ib_addr;
	uint32_t *rl_buffer;
	size_t rl_ib_size, packet_size_dwords;
	int retval;

	retval = pm_create_runlist_ib(pm, dqm_queues, &rl_gpu_ib_addr,
					&rl_ib_size);
	if (retval)
		goto fail_create_runlist_ib;

	pr_debug("runlist IB address: 0x%llX\n", rl_gpu_ib_addr);

	packet_size_dwords = pm->pmf->runlist_size / sizeof(uint32_t);
	mutex_lock(&pm->lock);

	retval = pm->priv_queue->ops.acquire_packet_buffer(pm->priv_queue,
					packet_size_dwords, &rl_buffer);
	if (retval)
		goto fail_acquire_packet_buffer;

	retval = pm->pmf->runlist(pm, rl_buffer, rl_gpu_ib_addr,
					rl_ib_size / sizeof(uint32_t), false);
	if (retval)
		goto fail_create_runlist;

	pm->priv_queue->ops.submit_packet(pm->priv_queue);

	mutex_unlock(&pm->lock);

	return retval;

fail_create_runlist:
	pm->priv_queue->ops.rollback_packet(pm->priv_queue);
fail_acquire_packet_buffer:
	mutex_unlock(&pm->lock);
fail_create_runlist_ib:
	pm_release_ib(pm);
	return retval;
}