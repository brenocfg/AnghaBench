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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_get_fcoe_info (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_get_iscsi_info (struct bnx2x*) ; 

__attribute__((used)) static void bnx2x_get_cnic_info(struct bnx2x *bp)
{
	/*
	 * iSCSI may be dynamically disabled but reading
	 * info here we will decrease memory usage by driver
	 * if the feature is disabled for good
	 */
	bnx2x_get_iscsi_info(bp);
	bnx2x_get_fcoe_info(bp);
}