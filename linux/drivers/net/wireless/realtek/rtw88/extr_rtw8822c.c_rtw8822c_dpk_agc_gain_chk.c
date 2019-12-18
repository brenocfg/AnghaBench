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
typedef  int u16 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_DPK_DAGC ; 
 int /*<<< orphan*/  RTW_DPK_GAIN_LARGE ; 
 int /*<<< orphan*/  RTW_DPK_GAIN_LESS ; 
 int rtw8822c_dpk_dgain_read (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822c_dpk_one_shot (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 rtw8822c_dpk_agc_gain_chk(struct rtw_dev *rtwdev, u8 path,
				    u8 limited_pga)
{
	u8 result = 0;
	u16 dgain;

	rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DAGC);
	dgain = rtw8822c_dpk_dgain_read(rtwdev, path);

	if (dgain > 1535 && !limited_pga)
		return RTW_DPK_GAIN_LESS;
	else if (dgain < 768 && !limited_pga)
		return RTW_DPK_GAIN_LARGE;
	else
		return result;
}