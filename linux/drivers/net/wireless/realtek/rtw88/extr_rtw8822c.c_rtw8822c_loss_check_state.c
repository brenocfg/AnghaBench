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
struct rtw8822c_dpk_data {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_DPK_GAIN_LOSS ; 
 int /*<<< orphan*/  rtw8822c_dpk_agc_loss_chk (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822c_dpk_one_shot (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 rtw8822c_loss_check_state(struct rtw_dev *rtwdev,
				    struct rtw8822c_dpk_data *data)
{
	u8 path = data->path;
	u8 state;

	rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_GAIN_LOSS);
	state = rtw8822c_dpk_agc_loss_chk(rtwdev, path);

	return state;
}