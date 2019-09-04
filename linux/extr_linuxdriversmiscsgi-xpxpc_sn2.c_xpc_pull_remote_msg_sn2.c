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
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;
struct xpc_partition {int dummy; } ;
struct xpc_msg_sn2 {int dummy; } ;
struct TYPE_4__ {unsigned long put; } ;
struct xpc_channel_sn2 {unsigned long next_msg_to_pull; unsigned long remote_msgqueue_pa; scalar_t__ remote_msgqueue; int /*<<< orphan*/  msg_to_pull_mutex; TYPE_2__ w_remote_GP; } ;
struct TYPE_3__ {struct xpc_channel_sn2 sn2; } ;
struct xpc_channel {size_t partid; unsigned long remote_nentries; unsigned long entry_size; int /*<<< orphan*/  number; TYPE_1__ sn; } ;
typedef  unsigned long s64 ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int /*<<< orphan*/  XPC_DEACTIVATE_PARTITION (struct xpc_partition*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int xpSuccess ; 
 int /*<<< orphan*/  xpc_chan ; 
 struct xpc_partition* xpc_partitions ; 
 int xpc_pull_remote_cachelines_sn2 (struct xpc_partition*,struct xpc_msg_sn2*,unsigned long,unsigned long) ; 

__attribute__((used)) static struct xpc_msg_sn2 *
xpc_pull_remote_msg_sn2(struct xpc_channel *ch, s64 get)
{
	struct xpc_partition *part = &xpc_partitions[ch->partid];
	struct xpc_channel_sn2 *ch_sn2 = &ch->sn.sn2;
	unsigned long remote_msg_pa;
	struct xpc_msg_sn2 *msg;
	u32 msg_index;
	u32 nmsgs;
	u64 msg_offset;
	enum xp_retval ret;

	if (mutex_lock_interruptible(&ch_sn2->msg_to_pull_mutex) != 0) {
		/* we were interrupted by a signal */
		return NULL;
	}

	while (get >= ch_sn2->next_msg_to_pull) {

		/* pull as many messages as are ready and able to be pulled */

		msg_index = ch_sn2->next_msg_to_pull % ch->remote_nentries;

		DBUG_ON(ch_sn2->next_msg_to_pull >= ch_sn2->w_remote_GP.put);
		nmsgs = ch_sn2->w_remote_GP.put - ch_sn2->next_msg_to_pull;
		if (msg_index + nmsgs > ch->remote_nentries) {
			/* ignore the ones that wrap the msg queue for now */
			nmsgs = ch->remote_nentries - msg_index;
		}

		msg_offset = msg_index * ch->entry_size;
		msg = (struct xpc_msg_sn2 *)((u64)ch_sn2->remote_msgqueue +
		    msg_offset);
		remote_msg_pa = ch_sn2->remote_msgqueue_pa + msg_offset;

		ret = xpc_pull_remote_cachelines_sn2(part, msg, remote_msg_pa,
						     nmsgs * ch->entry_size);
		if (ret != xpSuccess) {

			dev_dbg(xpc_chan, "failed to pull %d msgs starting with"
				" msg %lld from partition %d, channel=%d, "
				"ret=%d\n", nmsgs, ch_sn2->next_msg_to_pull,
				ch->partid, ch->number, ret);

			XPC_DEACTIVATE_PARTITION(part, ret);

			mutex_unlock(&ch_sn2->msg_to_pull_mutex);
			return NULL;
		}

		ch_sn2->next_msg_to_pull += nmsgs;
	}

	mutex_unlock(&ch_sn2->msg_to_pull_mutex);

	/* return the message we were looking for */
	msg_offset = (get % ch->remote_nentries) * ch->entry_size;
	msg = (struct xpc_msg_sn2 *)((u64)ch_sn2->remote_msgqueue + msg_offset);

	return msg;
}