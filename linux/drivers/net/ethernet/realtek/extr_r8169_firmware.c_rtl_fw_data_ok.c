#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct rtl_fw_phy_action {size_t size; int /*<<< orphan*/ * code; } ;
struct rtl_fw {int /*<<< orphan*/  dev; struct rtl_fw_phy_action phy_action; } ;

/* Variables and functions */
#define  PHY_BJMPN 140 
#define  PHY_CLEAR_READCOUNT 139 
#define  PHY_COMP_EQ_SKIPN 138 
#define  PHY_COMP_NEQ_SKIPN 137 
#define  PHY_DATA_AND 136 
#define  PHY_DATA_OR 135 
#define  PHY_DELAY_MS 134 
#define  PHY_MDIO_CHG 133 
#define  PHY_READ 132 
#define  PHY_READCOUNT_EQ_SKIP 131 
#define  PHY_SKIPN 130 
#define  PHY_WRITE 129 
#define  PHY_WRITE_PREVIOUS 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rtl_fw_data_ok(struct rtl_fw *rtl_fw)
{
	struct rtl_fw_phy_action *pa = &rtl_fw->phy_action;
	size_t index;

	for (index = 0; index < pa->size; index++) {
		u32 action = le32_to_cpu(pa->code[index]);
		u32 regno = (action & 0x0fff0000) >> 16;

		switch (action >> 28) {
		case PHY_READ:
		case PHY_DATA_OR:
		case PHY_DATA_AND:
		case PHY_MDIO_CHG:
		case PHY_CLEAR_READCOUNT:
		case PHY_WRITE:
		case PHY_WRITE_PREVIOUS:
		case PHY_DELAY_MS:
			break;

		case PHY_BJMPN:
			if (regno > index)
				goto out;
			break;
		case PHY_READCOUNT_EQ_SKIP:
			if (index + 2 >= pa->size)
				goto out;
			break;
		case PHY_COMP_EQ_SKIPN:
		case PHY_COMP_NEQ_SKIPN:
		case PHY_SKIPN:
			if (index + 1 + regno >= pa->size)
				goto out;
			break;

		default:
			dev_err(rtl_fw->dev, "Invalid action 0x%08x\n", action);
			return false;
		}
	}

	return true;
out:
	dev_err(rtl_fw->dev, "Out of range of firmware\n");
	return false;
}