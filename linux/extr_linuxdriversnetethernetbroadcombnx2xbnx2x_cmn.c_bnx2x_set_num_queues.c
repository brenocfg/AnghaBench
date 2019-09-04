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
struct bnx2x {int num_ethernet_queues; scalar_t__ num_queues; scalar_t__ num_cnic_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*,scalar_t__) ; 
 scalar_t__ CNIC_SUPPORT (struct bnx2x*) ; 
 scalar_t__ IS_MF_STORAGE_ONLY (struct bnx2x*) ; 
 int bnx2x_calc_num_queues (struct bnx2x*) ; 

void bnx2x_set_num_queues(struct bnx2x *bp)
{
	/* RSS queues */
	bp->num_ethernet_queues = bnx2x_calc_num_queues(bp);

	/* override in STORAGE SD modes */
	if (IS_MF_STORAGE_ONLY(bp))
		bp->num_ethernet_queues = 1;

	/* Add special queues */
	bp->num_cnic_queues = CNIC_SUPPORT(bp); /* For FCOE */
	bp->num_queues = bp->num_ethernet_queues + bp->num_cnic_queues;

	BNX2X_DEV_INFO("set number of queues to %d\n", bp->num_queues);
}