#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iscsi_stats_info {int /*<<< orphan*/  qos_priority; scalar_t__ mac_local; } ;
struct bnx2x_dcbx_app_params {int /*<<< orphan*/ * traffic_type_priority; } ;
struct TYPE_8__ {int /*<<< orphan*/  iscsi_mac; } ;
struct TYPE_5__ {struct bnx2x_dcbx_app_params app; } ;
struct bnx2x {TYPE_4__ cnic_eth_dev; TYPE_3__* slowpath; TYPE_1__ dcbx_port_params; } ;
struct TYPE_6__ {struct iscsi_stats_info iscsi_stat; } ;
struct TYPE_7__ {TYPE_2__ drv_info_to_mcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_CTL_ISCSI_STATS_GET_CMD ; 
 int /*<<< orphan*/  CNIC_LOADED (struct bnx2x*) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 size_t LLFC_TRAFFIC_TYPE_ISCSI ; 
 scalar_t__ MAC_PAD ; 
 int /*<<< orphan*/  bnx2x_cnic_notify (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_drv_info_iscsi_stat(struct bnx2x *bp)
{
	struct bnx2x_dcbx_app_params *app = &bp->dcbx_port_params.app;
	struct iscsi_stats_info *iscsi_stat =
		&bp->slowpath->drv_info_to_mcp.iscsi_stat;

	if (!CNIC_LOADED(bp))
		return;

	memcpy(iscsi_stat->mac_local + MAC_PAD, bp->cnic_eth_dev.iscsi_mac,
	       ETH_ALEN);

	iscsi_stat->qos_priority =
		app->traffic_type_priority[LLFC_TRAFFIC_TYPE_ISCSI];

	/* ask L5 driver to add data to the struct */
	bnx2x_cnic_notify(bp, CNIC_CTL_ISCSI_STATS_GET_CMD);
}