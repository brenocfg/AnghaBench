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
struct pf_vf_bulletin_content {int valid_bitmap; int link_flags; int /*<<< orphan*/  link_speed; } ;
struct bnx2x_virtf {scalar_t__ link_cfg; } ;
struct bnx2x_link_report_data {int /*<<< orphan*/  link_report_flags; int /*<<< orphan*/  line_speed; } ;
struct bnx2x {TYPE_1__* vfdb; struct bnx2x_link_report_data last_reported_link; } ;
struct TYPE_2__ {int /*<<< orphan*/  bulletin_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_FD ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_LINK_DOWN ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_RX_FC_ON ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_TX_FC_ON ; 
 int BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int,char*,int,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IFLA_VF_LINK_STATE_AUTO ; 
 scalar_t__ IFLA_VF_LINK_STATE_DISABLE ; 
 scalar_t__ IFLA_VF_LINK_STATE_ENABLE ; 
 int LINK_VALID ; 
 int NETIF_MSG_LINK ; 
 int VFPF_LINK_REPORT_FULL_DUPLEX ; 
 int VFPF_LINK_REPORT_LINK_DOWN ; 
 int VFPF_LINK_REPORT_RX_FC_ON ; 
 int VFPF_LINK_REPORT_TX_FC_ON ; 
 int /*<<< orphan*/  bnx2x_max_speed_cap (struct bnx2x*) ; 
 int bnx2x_post_vf_bulletin (struct bnx2x*,int) ; 
 int bnx2x_vf_op_prep (struct bnx2x*,int,struct bnx2x_virtf**,struct pf_vf_bulletin_content**,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnx2x_iov_link_update_vf(struct bnx2x *bp, int idx)
{
	struct bnx2x_link_report_data *state = &bp->last_reported_link;
	struct pf_vf_bulletin_content *bulletin;
	struct bnx2x_virtf *vf;
	bool update = true;
	int rc = 0;

	/* sanity and init */
	rc = bnx2x_vf_op_prep(bp, idx, &vf, &bulletin, false);
	if (rc)
		return rc;

	mutex_lock(&bp->vfdb->bulletin_mutex);

	if (vf->link_cfg == IFLA_VF_LINK_STATE_AUTO) {
		bulletin->valid_bitmap |= 1 << LINK_VALID;

		bulletin->link_speed = state->line_speed;
		bulletin->link_flags = 0;
		if (test_bit(BNX2X_LINK_REPORT_LINK_DOWN,
			     &state->link_report_flags))
			bulletin->link_flags |= VFPF_LINK_REPORT_LINK_DOWN;
		if (test_bit(BNX2X_LINK_REPORT_FD,
			     &state->link_report_flags))
			bulletin->link_flags |= VFPF_LINK_REPORT_FULL_DUPLEX;
		if (test_bit(BNX2X_LINK_REPORT_RX_FC_ON,
			     &state->link_report_flags))
			bulletin->link_flags |= VFPF_LINK_REPORT_RX_FC_ON;
		if (test_bit(BNX2X_LINK_REPORT_TX_FC_ON,
			     &state->link_report_flags))
			bulletin->link_flags |= VFPF_LINK_REPORT_TX_FC_ON;
	} else if (vf->link_cfg == IFLA_VF_LINK_STATE_DISABLE &&
		   !(bulletin->link_flags & VFPF_LINK_REPORT_LINK_DOWN)) {
		bulletin->valid_bitmap |= 1 << LINK_VALID;
		bulletin->link_flags |= VFPF_LINK_REPORT_LINK_DOWN;
	} else if (vf->link_cfg == IFLA_VF_LINK_STATE_ENABLE &&
		   (bulletin->link_flags & VFPF_LINK_REPORT_LINK_DOWN)) {
		bulletin->valid_bitmap |= 1 << LINK_VALID;
		bulletin->link_speed = bnx2x_max_speed_cap(bp);
		bulletin->link_flags &= ~VFPF_LINK_REPORT_LINK_DOWN;
	} else {
		update = false;
	}

	if (update) {
		DP(NETIF_MSG_LINK | BNX2X_MSG_IOV,
		   "vf %d mode %u speed %d flags %x\n", idx,
		   vf->link_cfg, bulletin->link_speed, bulletin->link_flags);

		/* Post update on VF's bulletin board */
		rc = bnx2x_post_vf_bulletin(bp, idx);
		if (rc) {
			BNX2X_ERR("failed to update VF[%d] bulletin\n", idx);
			goto out;
		}
	}

out:
	mutex_unlock(&bp->vfdb->bulletin_mutex);
	return rc;
}