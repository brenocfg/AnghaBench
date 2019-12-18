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
struct rtw_dev {int dummy; } ;
struct rtw8822c_dpk_data {int pga; int limited_pga; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RXAGC ; 
 int /*<<< orphan*/  RF_MODE_TRXAGC ; 
 int RTW_DPK_GAIN_CHECK ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 rtw8822c_gain_large_state(struct rtw_dev *rtwdev,
				    struct rtw8822c_dpk_data *data)
{
	u8 pga = data->pga;

	if (pga > 0xe)
		rtw_write_rf(rtwdev, data->path, RF_MODE_TRXAGC, BIT_RXAGC, 0xc);
	else if (pga > 0xb && pga < 0xf)
		rtw_write_rf(rtwdev, data->path, RF_MODE_TRXAGC, BIT_RXAGC, 0x0);
	else if (pga < 0xc)
		data->limited_pga = 1;

	return RTW_DPK_GAIN_CHECK;
}