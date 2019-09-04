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
struct hwrm_ring_cmpl_ring_cfg_aggint_params_input {int /*<<< orphan*/  ring_id; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  coal_bufs; int /*<<< orphan*/  coal_ticks; } ;
struct bnxt_cp_ring_info {TYPE_1__ rx_ring_coal; } ;
struct bnxt_napi {unsigned int index; int /*<<< orphan*/  rx_ring; struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt_coal {int /*<<< orphan*/  coal_bufs; int /*<<< orphan*/  coal_ticks; } ;
struct bnxt {TYPE_2__* grp_info; int /*<<< orphan*/  rx_coal; } ;
typedef  int /*<<< orphan*/  req_rx ;
struct TYPE_4__ {int /*<<< orphan*/  cp_fw_ring_id; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_ring_cmpl_ring_cfg_aggint_params_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_set_coal_params (struct bnxt_coal*,struct hwrm_ring_cmpl_ring_cfg_aggint_params_input*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_ring_cmpl_ring_cfg_aggint_params_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct bnxt_coal*,int /*<<< orphan*/ *,int) ; 

int bnxt_hwrm_set_ring_coal(struct bnxt *bp, struct bnxt_napi *bnapi)
{
	struct hwrm_ring_cmpl_ring_cfg_aggint_params_input req_rx = {0};
	struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	struct bnxt_coal coal;
	unsigned int grp_idx;

	/* Tick values in micro seconds.
	 * 1 coal_buf x bufs_per_record = 1 completion record.
	 */
	memcpy(&coal, &bp->rx_coal, sizeof(struct bnxt_coal));

	coal.coal_ticks = cpr->rx_ring_coal.coal_ticks;
	coal.coal_bufs = cpr->rx_ring_coal.coal_bufs;

	if (!bnapi->rx_ring)
		return -ENODEV;

	bnxt_hwrm_cmd_hdr_init(bp, &req_rx,
			       HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS, -1, -1);

	bnxt_hwrm_set_coal_params(&coal, &req_rx);

	grp_idx = bnapi->index;
	req_rx.ring_id = cpu_to_le16(bp->grp_info[grp_idx].cp_fw_ring_id);

	return hwrm_send_message(bp, &req_rx, sizeof(req_rx),
				 HWRM_CMD_TIMEOUT);
}