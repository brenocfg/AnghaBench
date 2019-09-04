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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct xpc_vars_part_sn2 {scalar_t__ magic; scalar_t__ GPs_pa; scalar_t__ openclose_args_pa; scalar_t__ chctl_amo_pa; scalar_t__ nchannels; int /*<<< orphan*/  notify_IRQ_phys_cpuid; int /*<<< orphan*/  notify_IRQ_nasid; } ;
struct xpc_partition_sn2 {int remote_vars_part_pa; scalar_t__ remote_GPs_pa; scalar_t__ remote_openclose_args_pa; int /*<<< orphan*/  notify_IRQ_phys_cpuid; int /*<<< orphan*/  notify_IRQ_nasid; struct amo* remote_chctl_amo_va; } ;
struct TYPE_3__ {struct xpc_partition_sn2 sn2; } ;
struct xpc_partition {scalar_t__ nchannels; TYPE_1__ sn; } ;
struct amo {int dummy; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_4__ {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int L1_CACHE_ALIGN (int) ; 
 int L1_CACHE_BYTES ; 
 short XPC_PARTID (struct xpc_partition*) ; 
 scalar_t__ XPC_VP_MAGIC1_SN2 ; 
 scalar_t__ XPC_VP_MAGIC2_SN2 ; 
 scalar_t__ __va (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,short,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,short,int) ; 
 int sn_partition_id ; 
 int xpBadMagic ; 
 int xpInvalidAddress ; 
 int xpRetry ; 
 int xpSuccess ; 
 int /*<<< orphan*/  xpc_chan ; 
 int xpc_pull_remote_cachelines_sn2 (struct xpc_partition*,struct xpc_vars_part_sn2*,unsigned long,int) ; 
 TYPE_2__* xpc_vars_part_sn2 ; 

__attribute__((used)) static enum xp_retval
xpc_pull_remote_vars_part_sn2(struct xpc_partition *part)
{
	struct xpc_partition_sn2 *part_sn2 = &part->sn.sn2;
	u8 buffer[L1_CACHE_BYTES * 2];
	struct xpc_vars_part_sn2 *pulled_entry_cacheline =
	    (struct xpc_vars_part_sn2 *)L1_CACHE_ALIGN((u64)buffer);
	struct xpc_vars_part_sn2 *pulled_entry;
	unsigned long remote_entry_cacheline_pa;
	unsigned long remote_entry_pa;
	short partid = XPC_PARTID(part);
	enum xp_retval ret;

	/* pull the cacheline that contains the variables we're interested in */

	DBUG_ON(part_sn2->remote_vars_part_pa !=
		L1_CACHE_ALIGN(part_sn2->remote_vars_part_pa));
	DBUG_ON(sizeof(struct xpc_vars_part_sn2) != L1_CACHE_BYTES / 2);

	remote_entry_pa = part_sn2->remote_vars_part_pa +
	    sn_partition_id * sizeof(struct xpc_vars_part_sn2);

	remote_entry_cacheline_pa = (remote_entry_pa & ~(L1_CACHE_BYTES - 1));

	pulled_entry = (struct xpc_vars_part_sn2 *)((u64)pulled_entry_cacheline
						    + (remote_entry_pa &
						    (L1_CACHE_BYTES - 1)));

	ret = xpc_pull_remote_cachelines_sn2(part, pulled_entry_cacheline,
					     remote_entry_cacheline_pa,
					     L1_CACHE_BYTES);
	if (ret != xpSuccess) {
		dev_dbg(xpc_chan, "failed to pull XPC vars_part from "
			"partition %d, ret=%d\n", partid, ret);
		return ret;
	}

	/* see if they've been set up yet */

	if (pulled_entry->magic != XPC_VP_MAGIC1_SN2 &&
	    pulled_entry->magic != XPC_VP_MAGIC2_SN2) {

		if (pulled_entry->magic != 0) {
			dev_dbg(xpc_chan, "partition %d's XPC vars_part for "
				"partition %d has bad magic value (=0x%llx)\n",
				partid, sn_partition_id, pulled_entry->magic);
			return xpBadMagic;
		}

		/* they've not been initialized yet */
		return xpRetry;
	}

	if (xpc_vars_part_sn2[partid].magic == XPC_VP_MAGIC1_SN2) {

		/* validate the variables */

		if (pulled_entry->GPs_pa == 0 ||
		    pulled_entry->openclose_args_pa == 0 ||
		    pulled_entry->chctl_amo_pa == 0) {

			dev_err(xpc_chan, "partition %d's XPC vars_part for "
				"partition %d are not valid\n", partid,
				sn_partition_id);
			return xpInvalidAddress;
		}

		/* the variables we imported look to be valid */

		part_sn2->remote_GPs_pa = pulled_entry->GPs_pa;
		part_sn2->remote_openclose_args_pa =
		    pulled_entry->openclose_args_pa;
		part_sn2->remote_chctl_amo_va =
		    (struct amo *)__va(pulled_entry->chctl_amo_pa);
		part_sn2->notify_IRQ_nasid = pulled_entry->notify_IRQ_nasid;
		part_sn2->notify_IRQ_phys_cpuid =
		    pulled_entry->notify_IRQ_phys_cpuid;

		if (part->nchannels > pulled_entry->nchannels)
			part->nchannels = pulled_entry->nchannels;

		/* let the other side know that we've pulled their variables */

		xpc_vars_part_sn2[partid].magic = XPC_VP_MAGIC2_SN2;
	}

	if (pulled_entry->magic == XPC_VP_MAGIC1_SN2)
		return xpRetry;

	return xpSuccess;
}