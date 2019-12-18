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
typedef  int /*<<< orphan*/  u8 ;
struct phy_device {int dummy; } ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_3__ {struct phy_device* phydev; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TP_MDI ; 
 int /*<<< orphan*/  ETH_TP_MDI_AUTO ; 
 int /*<<< orphan*/  ETH_TP_MDI_INVALID ; 
 int /*<<< orphan*/  ETH_TP_MDI_X ; 
 int /*<<< orphan*/  HCLGE_PHY_CSC_REG ; 
 int /*<<< orphan*/  HCLGE_PHY_CSS_REG ; 
 int /*<<< orphan*/  HCLGE_PHY_MDIX_CTRL_M ; 
 int /*<<< orphan*/  HCLGE_PHY_MDIX_CTRL_S ; 
 int /*<<< orphan*/  HCLGE_PHY_MDIX_STATUS_B ; 
 int /*<<< orphan*/  HCLGE_PHY_PAGE_COPPER ; 
 int /*<<< orphan*/  HCLGE_PHY_PAGE_MDIX ; 
 int /*<<< orphan*/  HCLGE_PHY_PAGE_REG ; 
 int /*<<< orphan*/  HCLGE_PHY_SPEED_DUP_RESOLVE_B ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hnae3_get_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int hnae3_get_field (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_get_mdix_mode(struct hnae3_handle *handle,
				u8 *tp_mdix_ctrl, u8 *tp_mdix)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	struct phy_device *phydev = hdev->hw.mac.phydev;
	int mdix_ctrl, mdix, is_resolved;
	unsigned int retval;

	if (!phydev) {
		*tp_mdix_ctrl = ETH_TP_MDI_INVALID;
		*tp_mdix = ETH_TP_MDI_INVALID;
		return;
	}

	phy_write(phydev, HCLGE_PHY_PAGE_REG, HCLGE_PHY_PAGE_MDIX);

	retval = phy_read(phydev, HCLGE_PHY_CSC_REG);
	mdix_ctrl = hnae3_get_field(retval, HCLGE_PHY_MDIX_CTRL_M,
				    HCLGE_PHY_MDIX_CTRL_S);

	retval = phy_read(phydev, HCLGE_PHY_CSS_REG);
	mdix = hnae3_get_bit(retval, HCLGE_PHY_MDIX_STATUS_B);
	is_resolved = hnae3_get_bit(retval, HCLGE_PHY_SPEED_DUP_RESOLVE_B);

	phy_write(phydev, HCLGE_PHY_PAGE_REG, HCLGE_PHY_PAGE_COPPER);

	switch (mdix_ctrl) {
	case 0x0:
		*tp_mdix_ctrl = ETH_TP_MDI;
		break;
	case 0x1:
		*tp_mdix_ctrl = ETH_TP_MDI_X;
		break;
	case 0x3:
		*tp_mdix_ctrl = ETH_TP_MDI_AUTO;
		break;
	default:
		*tp_mdix_ctrl = ETH_TP_MDI_INVALID;
		break;
	}

	if (!is_resolved)
		*tp_mdix = ETH_TP_MDI_INVALID;
	else if (mdix)
		*tp_mdix = ETH_TP_MDI_X;
	else
		*tp_mdix = ETH_TP_MDI;
}