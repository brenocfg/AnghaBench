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
struct mii_bus {struct hclge_dev* priv; } ;
struct hclge_mdio_cfg_cmd {int /*<<< orphan*/  data_rd; int /*<<< orphan*/  sta; int /*<<< orphan*/  ctrl_bit; int /*<<< orphan*/  phyad; int /*<<< orphan*/  phyid; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; int /*<<< orphan*/  state; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int HCLGE_MDIO_C22_READ ; 
 int /*<<< orphan*/  HCLGE_MDIO_CTRL_OP_M ; 
 int /*<<< orphan*/  HCLGE_MDIO_CTRL_OP_S ; 
 int /*<<< orphan*/  HCLGE_MDIO_CTRL_START_B ; 
 int /*<<< orphan*/  HCLGE_MDIO_CTRL_ST_M ; 
 int /*<<< orphan*/  HCLGE_MDIO_CTRL_ST_S ; 
 int /*<<< orphan*/  HCLGE_MDIO_PHYID_M ; 
 int /*<<< orphan*/  HCLGE_MDIO_PHYID_S ; 
 int /*<<< orphan*/  HCLGE_MDIO_PHYREG_M ; 
 int /*<<< orphan*/  HCLGE_MDIO_PHYREG_S ; 
 int /*<<< orphan*/  HCLGE_MDIO_STA_B ; 
 int /*<<< orphan*/  HCLGE_OPC_MDIO_CONFIG ; 
 int /*<<< orphan*/  HCLGE_STATE_CMD_DISABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hnae3_get_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_mdio_read(struct mii_bus *bus, int phyid, int regnum)
{
	struct hclge_mdio_cfg_cmd *mdio_cmd;
	struct hclge_dev *hdev = bus->priv;
	struct hclge_desc desc;
	int ret;

	if (test_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state))
		return 0;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MDIO_CONFIG, true);

	mdio_cmd = (struct hclge_mdio_cfg_cmd *)desc.data;

	hnae3_set_field(mdio_cmd->phyid, HCLGE_MDIO_PHYID_M,
			HCLGE_MDIO_PHYID_S, (u32)phyid);
	hnae3_set_field(mdio_cmd->phyad, HCLGE_MDIO_PHYREG_M,
			HCLGE_MDIO_PHYREG_S, (u32)regnum);

	hnae3_set_bit(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_START_B, 1);
	hnae3_set_field(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_ST_M,
			HCLGE_MDIO_CTRL_ST_S, 1);
	hnae3_set_field(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_OP_M,
			HCLGE_MDIO_CTRL_OP_S, HCLGE_MDIO_C22_READ);

	/* Read out phy data */
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"mdio read fail when get data, status is %d.\n",
			ret);
		return ret;
	}

	if (hnae3_get_bit(le16_to_cpu(mdio_cmd->sta), HCLGE_MDIO_STA_B)) {
		dev_err(&hdev->pdev->dev, "mdio read data error\n");
		return -EIO;
	}

	return le16_to_cpu(mdio_cmd->data_rd);
}