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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_FLAG_LEISURE_PS ; 
 int rtw_flag_check (struct rtw_dev*,int /*<<< orphan*/ ) ; 

bool rtw_in_lps(struct rtw_dev *rtwdev)
{
	return rtw_flag_check(rtwdev, RTW_FLAG_LEISURE_PS);
}