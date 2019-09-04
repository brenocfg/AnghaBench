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
typedef  int /*<<< orphan*/  u32 ;
struct vmbus_channel {scalar_t__ target_cpu; scalar_t__ affinity_policy; int /*<<< orphan*/  alloced_cpus_in_node; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_sc; int /*<<< orphan*/  sc_list; struct vmbus_channel* primary_channel; int /*<<< orphan*/  listentry; int /*<<< orphan*/  rescind; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ HV_LOCALIZED ; 
 int /*<<< orphan*/  cpumask_clear_cpu (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_channel (struct vmbus_channel*) ; 
 scalar_t__ get_cpu () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_channel_deq (struct vmbus_channel*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 struct vmbus_channel* relid2channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_call_function_single (scalar_t__,int /*<<< orphan*/  (*) (struct vmbus_channel*),struct vmbus_channel*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__ vmbus_connection ; 
 int /*<<< orphan*/  vmbus_release_relid (int /*<<< orphan*/ ) ; 

void hv_process_channel_removal(u32 relid)
{
	unsigned long flags;
	struct vmbus_channel *primary_channel, *channel;

	BUG_ON(!mutex_is_locked(&vmbus_connection.channel_mutex));

	/*
	 * Make sure channel is valid as we may have raced.
	 */
	channel = relid2channel(relid);
	if (!channel)
		return;

	BUG_ON(!channel->rescind);
	if (channel->target_cpu != get_cpu()) {
		put_cpu();
		smp_call_function_single(channel->target_cpu,
					 percpu_channel_deq, channel, true);
	} else {
		percpu_channel_deq(channel);
		put_cpu();
	}

	if (channel->primary_channel == NULL) {
		list_del(&channel->listentry);

		primary_channel = channel;
	} else {
		primary_channel = channel->primary_channel;
		spin_lock_irqsave(&primary_channel->lock, flags);
		list_del(&channel->sc_list);
		primary_channel->num_sc--;
		spin_unlock_irqrestore(&primary_channel->lock, flags);
	}

	/*
	 * We need to free the bit for init_vp_index() to work in the case
	 * of sub-channel, when we reload drivers like hv_netvsc.
	 */
	if (channel->affinity_policy == HV_LOCALIZED)
		cpumask_clear_cpu(channel->target_cpu,
				  &primary_channel->alloced_cpus_in_node);

	vmbus_release_relid(relid);

	free_channel(channel);
}