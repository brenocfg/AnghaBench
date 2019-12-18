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
typedef  int u16 ;
struct rtw_intf_phy_para {int cut_mask; int offset; int value; scalar_t__ ip_sel; } ;
struct TYPE_3__ {int cut_version; } ;
struct rtw_dev {TYPE_1__ hal; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {TYPE_2__* intf_table; } ;
struct TYPE_4__ {int n_gen1_para; int n_gen2_para; struct rtw_intf_phy_para* gen2_para; struct rtw_intf_phy_para* gen1_para; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ RTW_IP_SEL_PHY ; 
 int /*<<< orphan*/  rtw_dbi_write8 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_mdio_write (struct rtw_dev*,int,int,int) ; 

__attribute__((used)) static void rtw_pci_phy_cfg(struct rtw_dev *rtwdev)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_intf_phy_para *para;
	u16 cut;
	u16 value;
	u16 offset;
	int i;

	cut = BIT(0) << rtwdev->hal.cut_version;

	for (i = 0; i < chip->intf_table->n_gen1_para; i++) {
		para = &chip->intf_table->gen1_para[i];
		if (!(para->cut_mask & cut))
			continue;
		if (para->offset == 0xffff)
			break;
		offset = para->offset;
		value = para->value;
		if (para->ip_sel == RTW_IP_SEL_PHY)
			rtw_mdio_write(rtwdev, offset, value, true);
		else
			rtw_dbi_write8(rtwdev, offset, value);
	}

	for (i = 0; i < chip->intf_table->n_gen2_para; i++) {
		para = &chip->intf_table->gen2_para[i];
		if (!(para->cut_mask & cut))
			continue;
		if (para->offset == 0xffff)
			break;
		offset = para->offset;
		value = para->value;
		if (para->ip_sel == RTW_IP_SEL_PHY)
			rtw_mdio_write(rtwdev, offset, value, false);
		else
			rtw_dbi_write8(rtwdev, offset, value);
	}
}