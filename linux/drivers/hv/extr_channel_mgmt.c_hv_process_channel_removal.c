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
struct TYPE_3__ {scalar_t__ child_relid; } ;
struct vmbus_channel {scalar_t__ target_cpu; scalar_t__ affinity_policy; TYPE_1__ offermsg; int /*<<< orphan*/  alloced_cpus_in_node; int /*<<< orphan*/  lock; int /*<<< orphan*/  sc_list; struct vmbus_channel* primary_channel; int /*<<< orphan*/  listentry; int /*<<< orphan*/  rescind; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ HV_LOCALIZED ; 
 scalar_t__ INVALID_RELID ; 
 int /*<<< orphan*/  cpumask_clear_cpu (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_channel (struct vmbus_channel*) ; 
 scalar_t__ get_cpu () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_channel_deq (struct vmbus_channel*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_call_function_single (scalar_t__,int /*<<< orphan*/  (*) (struct vmbus_channel*),struct vmbus_channel*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_2__ vmbus_connection ; 
 int /*<<< orphan*/  vmbus_release_relid (scalar_t__) ; 

void hv_process_channel_removal(struct vmbus_channel *channel)
{
	struct vmbus_channel *primary_channel;
	unsigned long flags;

	BUG_ON(!mutex_is_locked(&vmbus_connection.channel_mutex));
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
		spin_unlock_irqrestore(&primary_channel->lock, flags);
	}

	/*
	 * We need to free the bit for init_vp_index() to work in the case
	 * of sub-channel, when we reload drivers like hv_netvsc.
	 */
	if (channel->affinity_policy == HV_LOCALIZED)
		cpumask_clear_cpu(channel->target_cpu,
				  &primary_channel->alloced_cpus_in_node);

	/*
	 * Upon suspend, an in-use hv_sock channel is marked as "rescinded" and
	 * the relid is invalidated; after hibernation, when the user-space app
	 * destroys the channel, the relid is INVALID_RELID, and in this case
	 * it's unnecessary and unsafe to release the old relid, since the same
	 * relid can refer to a completely different channel now.
	 */
	if (channel->offermsg.child_relid != INVALID_RELID)
		vmbus_release_relid(channel->offermsg.child_relid);

	free_channel(channel);
}