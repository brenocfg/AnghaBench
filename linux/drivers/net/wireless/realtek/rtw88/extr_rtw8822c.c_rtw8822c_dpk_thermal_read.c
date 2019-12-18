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
typedef  int /*<<< orphan*/  u8 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  RF_T_METER ; 
 int /*<<< orphan*/  rtw_read_rf (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 rtw8822c_dpk_thermal_read(struct rtw_dev *rtwdev, u8 path)
{
	rtw_write_rf(rtwdev, path, RF_T_METER, BIT(19), 0x1);
	rtw_write_rf(rtwdev, path, RF_T_METER, BIT(19), 0x0);
	rtw_write_rf(rtwdev, path, RF_T_METER, BIT(19), 0x1);
	udelay(15);

	return (u8)rtw_read_rf(rtwdev, path, RF_T_METER, 0x0007e);
}