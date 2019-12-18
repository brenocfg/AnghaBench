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
struct hclge_dev {TYPE_1__* pdev; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
struct hclge_dbg_bitmap_cmd {int /*<<< orphan*/  bit1; int /*<<< orphan*/  bit0; int /*<<< orphan*/  bit2; int /*<<< orphan*/  bit3; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_PG_DFX_STS ; 
 int /*<<< orphan*/  HCLGE_OPC_PORT_DFX_STS ; 
 int /*<<< orphan*/  HCLGE_OPC_PRI_DFX_STS ; 
 int /*<<< orphan*/  HCLGE_OPC_QSET_DFX_STS ; 
 int /*<<< orphan*/  HCLGE_OPC_SCH_NQ_CNT ; 
 int /*<<< orphan*/  HCLGE_OPC_SCH_RQ_CNT ; 
 int /*<<< orphan*/  HCLGE_OPC_TM_INTERNAL_CNT ; 
 int /*<<< orphan*/  HCLGE_OPC_TM_INTERNAL_STS ; 
 int /*<<< orphan*/  HCLGE_OPC_TM_INTERNAL_STS_1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int hclge_dbg_cmd_send (struct hclge_dev*,struct hclge_desc*,int,int,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static void hclge_dbg_dump_dcb(struct hclge_dev *hdev, const char *cmd_buf)
{
	struct device *dev = &hdev->pdev->dev;
	struct hclge_dbg_bitmap_cmd *bitmap;
	int rq_id, pri_id, qset_id;
	int port_id, nq_id, pg_id;
	struct hclge_desc desc[2];

	int cnt, ret;

	cnt = sscanf(cmd_buf, "%i %i %i %i %i %i",
		     &port_id, &pri_id, &pg_id, &rq_id, &nq_id, &qset_id);
	if (cnt != 6) {
		dev_err(&hdev->pdev->dev,
			"dump dcb: bad command parameter, cnt=%d\n", cnt);
		return;
	}

	ret = hclge_dbg_cmd_send(hdev, desc, qset_id, 1,
				 HCLGE_OPC_QSET_DFX_STS);
	if (ret)
		return;

	bitmap = (struct hclge_dbg_bitmap_cmd *)&desc[0].data[1];
	dev_info(dev, "roce_qset_mask: 0x%x\n", bitmap->bit0);
	dev_info(dev, "nic_qs_mask: 0x%x\n", bitmap->bit1);
	dev_info(dev, "qs_shaping_pass: 0x%x\n", bitmap->bit2);
	dev_info(dev, "qs_bp_sts: 0x%x\n", bitmap->bit3);

	ret = hclge_dbg_cmd_send(hdev, desc, pri_id, 1, HCLGE_OPC_PRI_DFX_STS);
	if (ret)
		return;

	bitmap = (struct hclge_dbg_bitmap_cmd *)&desc[0].data[1];
	dev_info(dev, "pri_mask: 0x%x\n", bitmap->bit0);
	dev_info(dev, "pri_cshaping_pass: 0x%x\n", bitmap->bit1);
	dev_info(dev, "pri_pshaping_pass: 0x%x\n", bitmap->bit2);

	ret = hclge_dbg_cmd_send(hdev, desc, pg_id, 1, HCLGE_OPC_PG_DFX_STS);
	if (ret)
		return;

	bitmap = (struct hclge_dbg_bitmap_cmd *)&desc[0].data[1];
	dev_info(dev, "pg_mask: 0x%x\n", bitmap->bit0);
	dev_info(dev, "pg_cshaping_pass: 0x%x\n", bitmap->bit1);
	dev_info(dev, "pg_pshaping_pass: 0x%x\n", bitmap->bit2);

	ret = hclge_dbg_cmd_send(hdev, desc, port_id, 1,
				 HCLGE_OPC_PORT_DFX_STS);
	if (ret)
		return;

	bitmap = (struct hclge_dbg_bitmap_cmd *)&desc[0].data[1];
	dev_info(dev, "port_mask: 0x%x\n", bitmap->bit0);
	dev_info(dev, "port_shaping_pass: 0x%x\n", bitmap->bit1);

	ret = hclge_dbg_cmd_send(hdev, desc, nq_id, 1, HCLGE_OPC_SCH_NQ_CNT);
	if (ret)
		return;

	dev_info(dev, "sch_nq_cnt: 0x%x\n", desc[0].data[1]);

	ret = hclge_dbg_cmd_send(hdev, desc, nq_id, 1, HCLGE_OPC_SCH_RQ_CNT);
	if (ret)
		return;

	dev_info(dev, "sch_rq_cnt: 0x%x\n", desc[0].data[1]);

	ret = hclge_dbg_cmd_send(hdev, desc, 0, 2, HCLGE_OPC_TM_INTERNAL_STS);
	if (ret)
		return;

	dev_info(dev, "pri_bp: 0x%x\n", desc[0].data[1]);
	dev_info(dev, "fifo_dfx_info: 0x%x\n", desc[0].data[2]);
	dev_info(dev, "sch_roce_fifo_afull_gap: 0x%x\n", desc[0].data[3]);
	dev_info(dev, "tx_private_waterline: 0x%x\n", desc[0].data[4]);
	dev_info(dev, "tm_bypass_en: 0x%x\n", desc[0].data[5]);
	dev_info(dev, "SSU_TM_BYPASS_EN: 0x%x\n", desc[1].data[0]);
	dev_info(dev, "SSU_RESERVE_CFG: 0x%x\n", desc[1].data[1]);

	ret = hclge_dbg_cmd_send(hdev, desc, port_id, 1,
				 HCLGE_OPC_TM_INTERNAL_CNT);
	if (ret)
		return;

	dev_info(dev, "SCH_NIC_NUM: 0x%x\n", desc[0].data[1]);
	dev_info(dev, "SCH_ROCE_NUM: 0x%x\n", desc[0].data[2]);

	ret = hclge_dbg_cmd_send(hdev, desc, port_id, 1,
				 HCLGE_OPC_TM_INTERNAL_STS_1);
	if (ret)
		return;

	dev_info(dev, "TC_MAP_SEL: 0x%x\n", desc[0].data[1]);
	dev_info(dev, "IGU_PFC_PRI_EN: 0x%x\n", desc[0].data[2]);
	dev_info(dev, "MAC_PFC_PRI_EN: 0x%x\n", desc[0].data[3]);
	dev_info(dev, "IGU_PRI_MAP_TC_CFG: 0x%x\n", desc[0].data[4]);
	dev_info(dev, "IGU_TX_PRI_MAP_TC_CFG: 0x%x\n", desc[0].data[5]);
}