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
typedef  int /*<<< orphan*/ * xpc_notify_func ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct xpc_partition {int nchannels; int /*<<< orphan*/ * channels; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_2__ {int (* send_payload ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int /*<<< orphan*/  XPC_N_CALL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*,short,int) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int xpUnknownReason ; 
 short xp_max_npartitions ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 scalar_t__ xpc_part_ref (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 

enum xp_retval
xpc_initiate_send_notify(short partid, int ch_number, u32 flags, void *payload,
			 u16 payload_size, xpc_notify_func func, void *key)
{
	struct xpc_partition *part = &xpc_partitions[partid];
	enum xp_retval ret = xpUnknownReason;

	dev_dbg(xpc_chan, "payload=0x%p, partid=%d, channel=%d\n", payload,
		partid, ch_number);

	DBUG_ON(partid < 0 || partid >= xp_max_npartitions);
	DBUG_ON(ch_number < 0 || ch_number >= part->nchannels);
	DBUG_ON(payload == NULL);
	DBUG_ON(func == NULL);

	if (xpc_part_ref(part)) {
		ret = xpc_arch_ops.send_payload(&part->channels[ch_number],
			  flags, payload, payload_size, XPC_N_CALL, func, key);
		xpc_part_deref(part);
	}
	return ret;
}