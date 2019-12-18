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
typedef  int u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_backup_vec (struct rtw_dev*,int,int,int,int) ; 
 int rtw8822c_get_path_read_addr (int) ; 
 int rtw8822c_get_path_write_addr (int) ; 

__attribute__((used)) static void rtw8822c_dac_cal_backup_path(struct rtw_dev *rtwdev, u8 path)
{
	u32 w_off = 0x1c;
	u32 r_off = 0x2c;
	u32 w_addr, r_addr;

	if (WARN_ON(path >= 2))
		return;

	/* backup I vector */
	w_addr = rtw8822c_get_path_write_addr(path) + 0xb0;
	r_addr = rtw8822c_get_path_read_addr(path) + 0x10;
	rtw8822c_dac_cal_backup_vec(rtwdev, path, 0, w_addr, r_addr);

	/* backup Q vector */
	w_addr = rtw8822c_get_path_write_addr(path) + 0xb0 + w_off;
	r_addr = rtw8822c_get_path_read_addr(path) + 0x10 + r_off;
	rtw8822c_dac_cal_backup_vec(rtwdev, path, 1, w_addr, r_addr);
}