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
struct xpc_partition {scalar_t__ remote_rp_pa; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 scalar_t__ XPC_RP_PART_NASIDS (scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xpPartitionDown ; 
 int /*<<< orphan*/  xp_pa (void*) ; 
 int xp_remote_memcpy (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_nasid_mask_nbytes ; 
 struct xpc_partition* xpc_partitions ; 

enum xp_retval
xpc_initiate_partid_to_nasids(short partid, void *nasid_mask)
{
	struct xpc_partition *part;
	unsigned long part_nasid_pa;

	part = &xpc_partitions[partid];
	if (part->remote_rp_pa == 0)
		return xpPartitionDown;

	memset(nasid_mask, 0, xpc_nasid_mask_nbytes);

	part_nasid_pa = (unsigned long)XPC_RP_PART_NASIDS(part->remote_rp_pa);

	return xp_remote_memcpy(xp_pa(nasid_mask), part_nasid_pa,
				xpc_nasid_mask_nbytes);
}