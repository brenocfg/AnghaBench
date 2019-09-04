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
struct bnx2x_virtf {int /*<<< orphan*/  mcast_obj; int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_mcast_ramrod_params {int mcast_list_len; int /*<<< orphan*/  mcast_list; int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/ * mcast_obj; } ;
struct bnx2x_mcast_list_elem {int /*<<< orphan*/  link; int /*<<< orphan*/  mac; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  bnx2x_mac_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MCAST_CMD_DEL ; 
 int /*<<< orphan*/  BNX2X_MCAST_CMD_SET ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int bnx2x_config_mcast (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int /*<<< orphan*/ ) ; 
 struct bnx2x_mcast_list_elem* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bnx2x_mcast_list_elem*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct bnx2x_mcast_ramrod_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnx2x_vf_mcast(struct bnx2x *bp, struct bnx2x_virtf *vf,
		   bnx2x_mac_addr_t *mcasts, int mc_num, bool drv_only)
{
	struct bnx2x_mcast_list_elem *mc = NULL;
	struct bnx2x_mcast_ramrod_params mcast;
	int rc, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	/* Prepare Multicast command */
	memset(&mcast, 0, sizeof(struct bnx2x_mcast_ramrod_params));
	mcast.mcast_obj = &vf->mcast_obj;
	if (drv_only)
		set_bit(RAMROD_DRV_CLR_ONLY, &mcast.ramrod_flags);
	else
		set_bit(RAMROD_COMP_WAIT, &mcast.ramrod_flags);
	if (mc_num) {
		mc = kcalloc(mc_num, sizeof(struct bnx2x_mcast_list_elem),
			     GFP_KERNEL);
		if (!mc) {
			BNX2X_ERR("Cannot Configure multicasts due to lack of memory\n");
			return -ENOMEM;
		}
	}

	if (mc_num) {
		INIT_LIST_HEAD(&mcast.mcast_list);
		for (i = 0; i < mc_num; i++) {
			mc[i].mac = mcasts[i];
			list_add_tail(&mc[i].link,
				      &mcast.mcast_list);
		}

		/* add new mcasts */
		mcast.mcast_list_len = mc_num;
		rc = bnx2x_config_mcast(bp, &mcast, BNX2X_MCAST_CMD_SET);
		if (rc)
			BNX2X_ERR("Failed to set multicasts\n");
	} else {
		/* clear existing mcasts */
		rc = bnx2x_config_mcast(bp, &mcast, BNX2X_MCAST_CMD_DEL);
		if (rc)
			BNX2X_ERR("Failed to remove multicasts\n");
	}

	kfree(mc);

	return rc;
}