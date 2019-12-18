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
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 scalar_t__ CONFIGURE_NIC_MODE (struct bnx2x*) ; 
 int /*<<< orphan*/  INITOP_SET ; 
 int /*<<< orphan*/  bnx2x_ilt_init_op_cnic (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_searcher (struct bnx2x*) ; 
 int bnx2x_reset_nic_mode (struct bnx2x*) ; 

int bnx2x_init_hw_func_cnic(struct bnx2x *bp)
{
	int rc;

	bnx2x_ilt_init_op_cnic(bp, INITOP_SET);

	if (CONFIGURE_NIC_MODE(bp)) {
		/* Configure searcher as part of function hw init */
		bnx2x_init_searcher(bp);

		/* Reset NIC mode */
		rc = bnx2x_reset_nic_mode(bp);
		if (rc)
			BNX2X_ERR("Can't change NIC mode!\n");
		return rc;
	}

	return 0;
}