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
typedef  size_t u8 ;
typedef  int u32 ;
struct rtw_dm_info {int* dack_adck; } ;
struct rtw_dev {struct rtw_dm_info dm_info; } ;

/* Variables and functions */
 size_t RF_PATH_A ; 
 int /*<<< orphan*/  check_hw_ready (struct rtw_dev*,int,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtw8822c_get_path_read_addr (size_t) ; 
 int rtw8822c_get_path_write_addr (size_t) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw8822c_dac_cal_step1(struct rtw_dev *rtwdev, u8 path)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 base_addr;
	u32 read_addr;

	base_addr = rtw8822c_get_path_write_addr(path);
	read_addr = rtw8822c_get_path_read_addr(path);

	rtw_write32(rtwdev, base_addr + 0x68, dm_info->dack_adck[path]);
	rtw_write32(rtwdev, base_addr + 0x0c, 0xdff00220);
	if (path == RF_PATH_A) {
		rtw_write32(rtwdev, base_addr + 0x60, 0xf0040ff0);
		rtw_write32(rtwdev, 0x1c38, 0xffffffff);
	}
	rtw_write32(rtwdev, base_addr + 0x10, 0x02d508c5);
	rtw_write32(rtwdev, 0x9b4, 0xdb66db00);
	rtw_write32(rtwdev, base_addr + 0xb0, 0x0a11fb88);
	rtw_write32(rtwdev, base_addr + 0xbc, 0x0008ff81);
	rtw_write32(rtwdev, base_addr + 0xc0, 0x0003d208);
	rtw_write32(rtwdev, base_addr + 0xcc, 0x0a11fb88);
	rtw_write32(rtwdev, base_addr + 0xd8, 0x0008ff81);
	rtw_write32(rtwdev, base_addr + 0xdc, 0x0003d208);
	rtw_write32(rtwdev, base_addr + 0xb8, 0x60000000);
	mdelay(2);
	rtw_write32(rtwdev, base_addr + 0xbc, 0x000aff8d);
	mdelay(2);
	rtw_write32(rtwdev, base_addr + 0xb0, 0x0a11fb89);
	rtw_write32(rtwdev, base_addr + 0xcc, 0x0a11fb89);
	mdelay(1);
	rtw_write32(rtwdev, base_addr + 0xb8, 0x62000000);
	rtw_write32(rtwdev, base_addr + 0xd4, 0x62000000);
	mdelay(20);
	if (!check_hw_ready(rtwdev, read_addr + 0x08, 0x7fff80, 0xffff) ||
	    !check_hw_ready(rtwdev, read_addr + 0x34, 0x7fff80, 0xffff))
		rtw_err(rtwdev, "failed to wait for dack ready\n");
	rtw_write32(rtwdev, base_addr + 0xb8, 0x02000000);
	mdelay(1);
	rtw_write32(rtwdev, base_addr + 0xbc, 0x0008ff87);
	rtw_write32(rtwdev, 0x9b4, 0xdb6db600);
	rtw_write32(rtwdev, base_addr + 0x10, 0x02d508c5);
	rtw_write32(rtwdev, base_addr + 0xbc, 0x0008ff87);
	rtw_write32(rtwdev, base_addr + 0x60, 0xf0000000);
}