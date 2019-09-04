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
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct port_info {int /*<<< orphan*/  port_id; TYPE_1__ dcb; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int idx; int /*<<< orphan*/  user_prio_map; int /*<<< orphan*/  protocolid; scalar_t__ sel_field; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_2__ app_priority; } ;
struct TYPE_8__ {TYPE_3__ dcb; } ;
struct fw_port_cmd {TYPE_4__ u; } ;
struct dcb_app {scalar_t__ priority; int /*<<< orphan*/  protocol; scalar_t__ selector; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  pcmd ;

/* Variables and functions */
 int CXGB4_MAX_DCBX_APP_SUPPORTED ; 
 int FW_PORT_DCB_CFG_SUCCESS ; 
 int /*<<< orphan*/  FW_PORT_DCB_TYPE_APP_ID ; 
 int /*<<< orphan*/  INIT_PORT_DCB_READ_PEER_CMD (struct fw_port_cmd,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_dcb_state_synced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ffs (int /*<<< orphan*/ ) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_port_cmd*,int,struct fw_port_cmd*) ; 

__attribute__((used)) static int cxgb4_getpeerapp_tbl(struct net_device *dev, struct dcb_app *table)
{
	struct fw_port_cmd pcmd;
	struct port_info *pi = netdev2pinfo(dev);
	struct adapter *adap = pi->adapter;
	int i, err = 0;

	if (!cxgb4_dcb_state_synced(pi->dcb.state))
		return 1;

	for (i = 0; i < CXGB4_MAX_DCBX_APP_SUPPORTED; i++) {
		INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);
		pcmd.u.dcb.app_priority.type = FW_PORT_DCB_TYPE_APP_ID;
		pcmd.u.dcb.app_priority.idx = i;
		err = t4_wr_mbox(adap, adap->mbox, &pcmd, sizeof(pcmd), &pcmd);

		if (err != FW_PORT_DCB_CFG_SUCCESS) {
			dev_err(adap->pdev_dev, "DCB app table read failed with %d\n",
				-err);
			return err;
		}

		/* find first empty slot */
		if (!pcmd.u.dcb.app_priority.protocolid)
			break;

		table[i].selector = (pcmd.u.dcb.app_priority.sel_field + 1);
		table[i].protocol =
			be16_to_cpu(pcmd.u.dcb.app_priority.protocolid);
		table[i].priority =
			ffs(pcmd.u.dcb.app_priority.user_prio_map) - 1;
	}
	return err;
}