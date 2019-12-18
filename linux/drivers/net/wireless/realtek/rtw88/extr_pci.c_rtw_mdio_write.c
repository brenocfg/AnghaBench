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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MDIO_WFLAG_V1 ; 
 int /*<<< orphan*/  REG_MDIO_V1 ; 
 scalar_t__ REG_PCIE_MIX_CFG ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int rtw_read32_mask (struct rtw_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rtw_mdio_write(struct rtw_dev *rtwdev, u8 addr, u16 data, bool g1)
{
	u8 page;
	u8 wflag;
	u8 cnt;

	rtw_write16(rtwdev, REG_MDIO_V1, data);

	page = addr < 0x20 ? 0 : 1;
	page += g1 ? 0 : 2;
	rtw_write8(rtwdev, REG_PCIE_MIX_CFG, addr & 0x1f);
	rtw_write8(rtwdev, REG_PCIE_MIX_CFG + 3, page);

	rtw_write32_mask(rtwdev, REG_PCIE_MIX_CFG, BIT_MDIO_WFLAG_V1, 1);
	wflag = rtw_read32_mask(rtwdev, REG_PCIE_MIX_CFG, BIT_MDIO_WFLAG_V1);

	cnt = 20;
	while (wflag && (cnt != 0)) {
		udelay(10);
		wflag = rtw_read32_mask(rtwdev, REG_PCIE_MIX_CFG,
					BIT_MDIO_WFLAG_V1);
		cnt--;
	}

	WARN(wflag, "MDIO write fail\n");
}