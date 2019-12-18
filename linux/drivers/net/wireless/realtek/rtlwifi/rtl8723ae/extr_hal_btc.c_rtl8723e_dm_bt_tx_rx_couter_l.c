#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ low_priority_rx; scalar_t__ low_priority_tx; } ;

/* Variables and functions */
 TYPE_1__ hal_coex_8723 ; 

__attribute__((used)) static u32 rtl8723e_dm_bt_tx_rx_couter_l(struct ieee80211_hw *hw)
{
	u32 counters = 0;

	counters = hal_coex_8723.low_priority_tx +
			hal_coex_8723.low_priority_rx;
	return counters;
}