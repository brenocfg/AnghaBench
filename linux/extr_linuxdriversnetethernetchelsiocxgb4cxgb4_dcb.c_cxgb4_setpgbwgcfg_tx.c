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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {scalar_t__ state; } ;
struct port_info {TYPE_4__ dcb; int /*<<< orphan*/  port_id; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pgrate; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ pgrate; } ;
struct TYPE_7__ {TYPE_2__ dcb; } ;
struct fw_port_cmd {int /*<<< orphan*/  op_to_portid; TYPE_3__ u; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  pcmd ;

/* Variables and functions */
 scalar_t__ CXGB4_DCB_STATE_HOST ; 
 int /*<<< orphan*/  FW_PORT_CMD_APPLY_F ; 
 int FW_PORT_DCB_CFG_SUCCESS ; 
 int /*<<< orphan*/  FW_PORT_DCB_TYPE_PGRATE ; 
 int /*<<< orphan*/  INIT_PORT_DCB_READ_LOCAL_CMD (struct fw_port_cmd,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_PORT_DCB_WRITE_CMD (struct fw_port_cmd,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_port_cmd*,int,struct fw_port_cmd*) ; 

__attribute__((used)) static void cxgb4_setpgbwgcfg_tx(struct net_device *dev, int pgid,
				 u8 bw_per)
{
	struct fw_port_cmd pcmd;
	struct port_info *pi = netdev2pinfo(dev);
	struct adapter *adap = pi->adapter;
	int err;

	INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
	pcmd.u.dcb.pgrate.type = FW_PORT_DCB_TYPE_PGRATE;

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, sizeof(pcmd), &pcmd);
	if (err != FW_PORT_DCB_CFG_SUCCESS) {
		dev_err(adap->pdev_dev, "DCB read PGRATE failed with %d\n",
			-err);
		return;
	}

	pcmd.u.dcb.pgrate.pgrate[pgid] = bw_per;

	INIT_PORT_DCB_WRITE_CMD(pcmd, pi->port_id);
	if (pi->dcb.state == CXGB4_DCB_STATE_HOST)
		pcmd.op_to_portid |= cpu_to_be32(FW_PORT_CMD_APPLY_F);

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, sizeof(pcmd), &pcmd);

	if (err != FW_PORT_DCB_CFG_SUCCESS)
		dev_err(adap->pdev_dev, "DCB write PGRATE failed with %d\n",
			-err);
}