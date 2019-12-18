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
typedef  void* u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {scalar_t__ state; } ;
struct port_info {TYPE_1__ dcb; int /*<<< orphan*/  port_id; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int idx; void* user_prio_map; void* sel_field; scalar_t__ protocolid; void* type; } ;
struct TYPE_7__ {TYPE_2__ app_priority; } ;
struct TYPE_8__ {TYPE_3__ dcb; } ;
struct fw_port_cmd {TYPE_4__ u; int /*<<< orphan*/  op_to_portid; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  pcmd ;

/* Variables and functions */
 scalar_t__ CXGB4_DCB_STATE_HOST ; 
 int CXGB4_MAX_DCBX_APP_SUPPORTED ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOLINK ; 
 int /*<<< orphan*/  FW_PORT_CMD_APPLY_F ; 
 int FW_PORT_DCB_CFG_SUCCESS ; 
 void* FW_PORT_DCB_TYPE_APP_ID ; 
 int /*<<< orphan*/  INIT_PORT_DCB_READ_LOCAL_CMD (struct fw_port_cmd,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_PORT_DCB_WRITE_CMD (struct fw_port_cmd,int /*<<< orphan*/ ) ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_dcb_state_synced (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_port_cmd*,int,struct fw_port_cmd*) ; 

__attribute__((used)) static int __cxgb4_setapp(struct net_device *dev, u8 app_idtype, u16 app_id,
			  u8 app_prio)
{
	struct fw_port_cmd pcmd;
	struct port_info *pi = netdev2pinfo(dev);
	struct adapter *adap = pi->adapter;
	int i, err;


	if (!cxgb4_dcb_state_synced(pi->dcb.state))
		return -EINVAL;

	/* DCB info gets thrown away on link up */
	if (!netif_carrier_ok(dev))
		return -ENOLINK;

	for (i = 0; i < CXGB4_MAX_DCBX_APP_SUPPORTED; i++) {
		INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
		pcmd.u.dcb.app_priority.type = FW_PORT_DCB_TYPE_APP_ID;
		pcmd.u.dcb.app_priority.idx = i;
		err = t4_wr_mbox(adap, adap->mbox, &pcmd, sizeof(pcmd), &pcmd);

		if (err != FW_PORT_DCB_CFG_SUCCESS) {
			dev_err(adap->pdev_dev, "DCB app table read failed with %d\n",
				-err);
			return err;
		}
		if (be16_to_cpu(pcmd.u.dcb.app_priority.protocolid) == app_id) {
			/* overwrite existing app table */
			pcmd.u.dcb.app_priority.protocolid = 0;
			break;
		}
		/* find first empty slot */
		if (!pcmd.u.dcb.app_priority.protocolid)
			break;
	}

	if (i == CXGB4_MAX_DCBX_APP_SUPPORTED) {
		/* no empty slots available */
		dev_err(adap->pdev_dev, "DCB app table full\n");
		return -EBUSY;
	}

	/* write out new app table entry */
	INIT_PORT_DCB_WRITE_CMD(pcmd, pi->port_id);
	if (pi->dcb.state == CXGB4_DCB_STATE_HOST)
		pcmd.op_to_portid |= cpu_to_be32(FW_PORT_CMD_APPLY_F);

	pcmd.u.dcb.app_priority.type = FW_PORT_DCB_TYPE_APP_ID;
	pcmd.u.dcb.app_priority.protocolid = cpu_to_be16(app_id);
	pcmd.u.dcb.app_priority.sel_field = app_idtype;
	pcmd.u.dcb.app_priority.user_prio_map = app_prio;
	pcmd.u.dcb.app_priority.idx = i;

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, sizeof(pcmd), &pcmd);
	if (err != FW_PORT_DCB_CFG_SUCCESS) {
		dev_err(adap->pdev_dev, "DCB app table write failed with %d\n",
			-err);
		return err;
	}

	return 0;
}