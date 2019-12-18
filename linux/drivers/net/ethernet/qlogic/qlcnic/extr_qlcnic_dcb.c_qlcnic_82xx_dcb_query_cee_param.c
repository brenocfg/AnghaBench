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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct qlcnic_dcb_param {void** app; void** pg_tsa_map; void** pg_bw_map; void** prio_pg_map; void** hdr_prio_pfc_map; } ;
struct qlcnic_dcb {struct qlcnic_adapter* adapter; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ req; } ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct qlcnic_82xx_dcb_param_mbx_le {int /*<<< orphan*/ * app; int /*<<< orphan*/ * pg_tsa_map; int /*<<< orphan*/ * pg_bw_map; int /*<<< orphan*/ * prio_pg_map; int /*<<< orphan*/ * hdr_prio_pfc_map; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LSD (int /*<<< orphan*/ ) ; 
 int MSD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCNIC_CMD_DCB_QUERY_PARAM ; 
#define  QLC_DCB_LOCAL_PARAM_FWID 130 
 int QLC_DCB_MAX_APP ; 
#define  QLC_DCB_OPER_PARAM_FWID 129 
#define  QLC_DCB_PEER_PARAM_FWID 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,void*,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,struct qlcnic_dcb_param*,int) ; 
 int /*<<< orphan*/  memset (struct qlcnic_dcb_param*,int /*<<< orphan*/ ,int) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

__attribute__((used)) static int qlcnic_82xx_dcb_query_cee_param(struct qlcnic_dcb *dcb,
					   char *buf, u8 type)
{
	u16 size = sizeof(struct qlcnic_82xx_dcb_param_mbx_le);
	struct qlcnic_adapter *adapter = dcb->adapter;
	struct qlcnic_82xx_dcb_param_mbx_le *prsp_le;
	struct device *dev = &adapter->pdev->dev;
	dma_addr_t cardrsp_phys_addr;
	struct qlcnic_dcb_param rsp;
	struct qlcnic_cmd_args cmd;
	u64 phys_addr;
	void *addr;
	int err, i;

	switch (type) {
	case QLC_DCB_LOCAL_PARAM_FWID:
	case QLC_DCB_OPER_PARAM_FWID:
	case QLC_DCB_PEER_PARAM_FWID:
		break;
	default:
		dev_err(dev, "Invalid parameter type %d\n", type);
		return -EINVAL;
	}

	addr = dma_alloc_coherent(dev, size, &cardrsp_phys_addr, GFP_KERNEL);
	if (addr == NULL)
		return -ENOMEM;

	prsp_le = addr;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DCB_QUERY_PARAM);
	if (err)
		goto out_free_rsp;

	phys_addr = cardrsp_phys_addr;
	cmd.req.arg[1] = size | (type << 16);
	cmd.req.arg[2] = MSD(phys_addr);
	cmd.req.arg[3] = LSD(phys_addr);

	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err) {
		dev_err(dev, "Failed to query DCBX parameter, err %d\n", err);
		goto out;
	}

	memset(&rsp, 0, sizeof(struct qlcnic_dcb_param));
	rsp.hdr_prio_pfc_map[0] = le32_to_cpu(prsp_le->hdr_prio_pfc_map[0]);
	rsp.hdr_prio_pfc_map[1] = le32_to_cpu(prsp_le->hdr_prio_pfc_map[1]);
	rsp.prio_pg_map[0] = le32_to_cpu(prsp_le->prio_pg_map[0]);
	rsp.prio_pg_map[1] = le32_to_cpu(prsp_le->prio_pg_map[1]);
	rsp.pg_bw_map[0] = le32_to_cpu(prsp_le->pg_bw_map[0]);
	rsp.pg_bw_map[1] = le32_to_cpu(prsp_le->pg_bw_map[1]);
	rsp.pg_tsa_map[0] = le32_to_cpu(prsp_le->pg_tsa_map[0]);
	rsp.pg_tsa_map[1] = le32_to_cpu(prsp_le->pg_tsa_map[1]);

	for (i = 0; i < QLC_DCB_MAX_APP; i++)
		rsp.app[i] = le32_to_cpu(prsp_le->app[i]);

	if (buf)
		memcpy(buf, &rsp, size);
out:
	qlcnic_free_mbx_args(&cmd);

out_free_rsp:
	dma_free_coherent(dev, size, addr, cardrsp_phys_addr);

	return err;
}