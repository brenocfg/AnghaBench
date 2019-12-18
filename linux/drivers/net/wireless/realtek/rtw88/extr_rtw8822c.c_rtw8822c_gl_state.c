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
struct rtw8822c_dpk_data {int txbb; scalar_t__ limited_pga; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_GAIN_TXBB ; 
 int /*<<< orphan*/  RF_TX_GAIN ; 
 int RTW_DPK_AGC_OUT ; 
 int RTW_DPK_GAIN_CHECK ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 rtw8822c_gl_state(struct rtw_dev *rtwdev,
			    struct rtw8822c_dpk_data *data, u8 is_large)
{
	u8 txbb_bound[] = {0x1f, 0};

	if (data->txbb == txbb_bound[is_large])
		return RTW_DPK_AGC_OUT;

	if (is_large == 1)
		data->txbb -= 2;
	else
		data->txbb += 3;

	rtw_write_rf(rtwdev, data->path, RF_TX_GAIN, BIT_GAIN_TXBB, data->txbb);
	data->limited_pga = 0;

	return RTW_DPK_GAIN_CHECK;
}