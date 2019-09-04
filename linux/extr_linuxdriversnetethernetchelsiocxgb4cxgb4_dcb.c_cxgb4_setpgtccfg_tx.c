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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_10__ {scalar_t__ state; } ;
struct port_info {TYPE_5__ dcb; int /*<<< orphan*/  port_id; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {scalar_t__* pgrate; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  pgid; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_2__ pgrate; TYPE_1__ pgid; } ;
struct TYPE_9__ {TYPE_3__ dcb; } ;
struct fw_port_cmd {int /*<<< orphan*/  op_to_portid; TYPE_4__ u; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  pcmd ;

/* Variables and functions */
 scalar_t__ CXGB4_DCB_STATE_HOST ; 
 scalar_t__ DCB_ATTR_VALUE_UNDEFINED ; 
 int FW_PORT_CMD_APPLY_F ; 
 int FW_PORT_DCB_CFG_SUCCESS ; 
 int /*<<< orphan*/  FW_PORT_DCB_TYPE_PGID ; 
 int /*<<< orphan*/  FW_PORT_DCB_TYPE_PGRATE ; 
 int /*<<< orphan*/  INIT_PORT_DCB_READ_LOCAL_CMD (struct fw_port_cmd,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_PORT_DCB_WRITE_CMD (struct fw_port_cmd,int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct fw_port_cmd*,int /*<<< orphan*/ ,int) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_port_cmd*,int,struct fw_port_cmd*) ; 

__attribute__((used)) static void cxgb4_setpgtccfg_tx(struct net_device *dev, int tc,
				u8 prio_type, u8 pgid, u8 bw_per,
				u8 up_tc_map)
{
	struct fw_port_cmd pcmd;
	struct port_info *pi = netdev2pinfo(dev);
	struct adapter *adap = pi->adapter;
	int fw_tc = 7 - tc;
	u32 _pgid;
	int err;

	if (pgid == DCB_ATTR_VALUE_UNDEFINED)
		return;
	if (bw_per == DCB_ATTR_VALUE_UNDEFINED)
		return;

	INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
	pcmd.u.dcb.pgid.type = FW_PORT_DCB_TYPE_PGID;

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, sizeof(pcmd), &pcmd);
	if (err != FW_PORT_DCB_CFG_SUCCESS) {
		dev_err(adap->pdev_dev, "DCB read PGID failed with %d\n", -err);
		return;
	}

	_pgid = be32_to_cpu(pcmd.u.dcb.pgid.pgid);
	_pgid &= ~(0xF << (fw_tc * 4));
	_pgid |= pgid << (fw_tc * 4);
	pcmd.u.dcb.pgid.pgid = cpu_to_be32(_pgid);

	INIT_PORT_DCB_WRITE_CMD(pcmd, pi->port_id);

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, sizeof(pcmd), &pcmd);
	if (err != FW_PORT_DCB_CFG_SUCCESS) {
		dev_err(adap->pdev_dev, "DCB write PGID failed with %d\n",
			-err);
		return;
	}

	memset(&pcmd, 0, sizeof(struct fw_port_cmd));

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