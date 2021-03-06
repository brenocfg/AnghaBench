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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {struct hclge_dev* priv; } ;
struct hclge_mdio_cfg_cmd {int /*<<< orphan*/  data_wr; int /*<<< orphan*/  ctrl_bit; int /*<<< orphan*/  phyad; int /*<<< orphan*/  phyid; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; int /*<<< orphan*/  state; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HCLGE_MDIO_C22_WRITE ; 
 int /*<<< orphan*/  HCLGE_MDIO_CTRL_OP_M ; 
 int /*<<< orphan*/  HCLGE_MDIO_CTRL_OP_S ; 
 int /*<<< orphan*/  HCLGE_MDIO_CTRL_START_B ; 
 int /*<<< orphan*/  HCLGE_MDIO_CTRL_ST_M ; 
 int /*<<< orphan*/  HCLGE_MDIO_CTRL_ST_S ; 
 int /*<<< orphan*/  HCLGE_MDIO_PHYID_M ; 
 int /*<<< orphan*/  HCLGE_MDIO_PHYID_S ; 
 int /*<<< orphan*/  HCLGE_MDIO_PHYREG_M ; 
 int /*<<< orphan*/  HCLGE_MDIO_PHYREG_S ; 
 int /*<<< orphan*/  HCLGE_OPC_MDIO_CONFIG ; 
 int /*<<< orphan*/  HCLGE_STATE_CMD_DISABLE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_mdio_write(struct mii_bus *bus, int phyid, int regnum,
			    u16 data)
{
	struct hclge_mdio_cfg_cmd *mdio_cmd;
	struct hclge_dev *hdev = bus->priv;
	struct hclge_desc desc;
	int ret;

	if (test_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state))
		return 0;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MDIO_CONFIG, false);

	mdio_cmd = (struct hclge_mdio_cfg_cmd *)desc.data;

	hnae3_set_field(mdio_cmd->phyid, HCLGE_MDIO_PHYID_M,
			HCLGE_MDIO_PHYID_S, (u32)phyid);
	hnae3_set_field(mdio_cmd->phyad, HCLGE_MDIO_PHYREG_M,
			HCLGE_MDIO_PHYREG_S, (u32)regnum);

	hnae3_set_bit(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_START_B, 1);
	hnae3_set_field(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_ST_M,
			HCLGE_MDIO_CTRL_ST_S, 1);
	hnae3_set_field(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_OP_M,
			HCLGE_MDIO_CTRL_OP_S, HCLGE_MDIO_C22_WRITE);

	mdio_cmd->data_wr = cpu_to_le16(data);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"mdio write fail when sending cmd, status is %d.\n",
			ret);
		return ret;
	}

	return 0;
}