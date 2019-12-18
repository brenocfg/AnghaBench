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
typedef  int /*<<< orphan*/  u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ rtw8822c_dpk_coef_read (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822c_dpk_fill_result (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool rtw8822c_dpk_check_pass(struct rtw_dev *rtwdev, bool is_fail,
				    u32 dpk_txagc, u8 path)
{
	bool result;

	if (!is_fail) {
		if (rtw8822c_dpk_coef_read(rtwdev, path))
			result = true;
		else
			result = false;
	} else {
		result = false;
	}

	rtw8822c_dpk_fill_result(rtwdev, dpk_txagc, path, result);

	return result;
}