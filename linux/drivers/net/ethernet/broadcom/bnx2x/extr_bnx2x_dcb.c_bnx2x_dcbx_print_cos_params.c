#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct bnx2x_func_tx_start_params {TYPE_5__* traffic_type_to_priority_cos; int /*<<< orphan*/  dcb_version; } ;
struct TYPE_8__ {size_t num_of_cos; TYPE_2__* cos_params; } ;
struct TYPE_6__ {int /*<<< orphan*/  priority_non_pauseable_mask; } ;
struct TYPE_9__ {TYPE_3__ ets; TYPE_1__ pfc; } ;
struct bnx2x {TYPE_4__ dcbx_port_params; } ;
struct TYPE_10__ {int /*<<< orphan*/  cos; int /*<<< orphan*/  priority; } ;
struct TYPE_7__ {int /*<<< orphan*/  pauseable; int /*<<< orphan*/  strict; int /*<<< orphan*/  bw_tbl; int /*<<< orphan*/  pri_bitmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_DCB ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,size_t,...) ; 
 size_t LLFC_DRIVER_TRAFFIC_TYPE_MAX ; 

__attribute__((used)) static void
bnx2x_dcbx_print_cos_params(struct bnx2x *bp,
			    struct bnx2x_func_tx_start_params *pfc_fw_cfg)
{
	u8 pri = 0;
	u8 cos = 0;

	DP(BNX2X_MSG_DCB,
	   "pfc_fw_cfg->dcb_version %x\n", pfc_fw_cfg->dcb_version);
	DP(BNX2X_MSG_DCB,
	   "pdev->params.dcbx_port_params.pfc.priority_non_pauseable_mask %x\n",
	   bp->dcbx_port_params.pfc.priority_non_pauseable_mask);

	for (cos = 0 ; cos < bp->dcbx_port_params.ets.num_of_cos ; cos++) {
		DP(BNX2X_MSG_DCB,
		   "pdev->params.dcbx_port_params.ets.cos_params[%d].pri_bitmask %x\n",
		   cos, bp->dcbx_port_params.ets.cos_params[cos].pri_bitmask);

		DP(BNX2X_MSG_DCB,
		   "pdev->params.dcbx_port_params.ets.cos_params[%d].bw_tbl %x\n",
		   cos, bp->dcbx_port_params.ets.cos_params[cos].bw_tbl);

		DP(BNX2X_MSG_DCB,
		   "pdev->params.dcbx_port_params.ets.cos_params[%d].strict %x\n",
		   cos, bp->dcbx_port_params.ets.cos_params[cos].strict);

		DP(BNX2X_MSG_DCB,
		   "pdev->params.dcbx_port_params.ets.cos_params[%d].pauseable %x\n",
		   cos, bp->dcbx_port_params.ets.cos_params[cos].pauseable);
	}

	for (pri = 0; pri < LLFC_DRIVER_TRAFFIC_TYPE_MAX; pri++) {
		DP(BNX2X_MSG_DCB,
		   "pfc_fw_cfg->traffic_type_to_priority_cos[%d].priority %x\n",
		   pri, pfc_fw_cfg->traffic_type_to_priority_cos[pri].priority);

		DP(BNX2X_MSG_DCB,
		   "pfc_fw_cfg->traffic_type_to_priority_cos[%d].cos %x\n",
		   pri, pfc_fw_cfg->traffic_type_to_priority_cos[pri].cos);
	}
}