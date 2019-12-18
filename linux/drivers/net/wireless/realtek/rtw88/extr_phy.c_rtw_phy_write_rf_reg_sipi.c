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
struct rtw_hal {int rf_path_num; } ;
struct rtw_dev {struct rtw_chip_info* chip; struct rtw_hal hal; } ;
struct rtw_chip_info {int* rf_sipi_addr; } ;
typedef  int old_data ;
typedef  enum rtw_rf_path { ____Placeholder_rtw_rf_path } rtw_rf_path ;

/* Variables and functions */
 int INV_RF_DATA ; 
 int RFREG_MASK ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*,...) ; 
 int rtw_phy_read_rf (struct rtw_dev*,int,int,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool rtw_phy_write_rf_reg_sipi(struct rtw_dev *rtwdev, enum rtw_rf_path rf_path,
			       u32 addr, u32 mask, u32 data)
{
	struct rtw_hal *hal = &rtwdev->hal;
	struct rtw_chip_info *chip = rtwdev->chip;
	u32 *sipi_addr = chip->rf_sipi_addr;
	u32 data_and_addr;
	u32 old_data = 0;
	u32 shift;

	if (rf_path >= hal->rf_path_num) {
		rtw_err(rtwdev, "unsupported rf path (%d)\n", rf_path);
		return false;
	}

	addr &= 0xff;
	mask &= RFREG_MASK;

	if (mask != RFREG_MASK) {
		old_data = rtw_phy_read_rf(rtwdev, rf_path, addr, RFREG_MASK);

		if (old_data == INV_RF_DATA) {
			rtw_err(rtwdev, "Write fail, rf is disabled\n");
			return false;
		}

		shift = __ffs(mask);
		data = ((old_data) & (~mask)) | (data << shift);
	}

	data_and_addr = ((addr << 20) | (data & 0x000fffff)) & 0x0fffffff;

	rtw_write32(rtwdev, sipi_addr[rf_path], data_and_addr);

	udelay(13);

	return true;
}