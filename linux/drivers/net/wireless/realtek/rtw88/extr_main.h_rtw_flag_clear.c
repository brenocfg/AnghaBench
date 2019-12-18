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
struct rtw_dev {int /*<<< orphan*/  flags; } ;
typedef  enum rtw_flags { ____Placeholder_rtw_flags } rtw_flags ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rtw_flag_clear(struct rtw_dev *rtwdev, enum rtw_flags flag)
{
	clear_bit(flag, rtwdev->flags);
}