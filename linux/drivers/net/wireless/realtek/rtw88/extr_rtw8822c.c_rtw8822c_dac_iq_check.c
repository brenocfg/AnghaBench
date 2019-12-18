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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_DBG_RFK ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool rtw8822c_dac_iq_check(struct rtw_dev *rtwdev, u32 value)
{
	bool ret = true;

	if ((value >= 0x200 && (0x400 - value) > 0x64) ||
	    (value < 0x200 && value > 0x64)) {
		ret = false;
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] Error overflow\n");
	}

	return ret;
}