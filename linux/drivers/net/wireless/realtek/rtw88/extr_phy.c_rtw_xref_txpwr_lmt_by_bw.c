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
typedef  scalar_t__ u8 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTW_CHANNEL_WIDTH_20 ; 
 scalar_t__ RTW_CHANNEL_WIDTH_40 ; 
 int /*<<< orphan*/  rtw_xref_5g_txpwr_lmt_by_ch (struct rtw_dev*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
rtw_xref_txpwr_lmt_by_bw(struct rtw_dev *rtwdev, u8 regd)
{
	u8 bw;

	for (bw = RTW_CHANNEL_WIDTH_20; bw <= RTW_CHANNEL_WIDTH_40; bw++)
		rtw_xref_5g_txpwr_lmt_by_ch(rtwdev, regd, bw);
}