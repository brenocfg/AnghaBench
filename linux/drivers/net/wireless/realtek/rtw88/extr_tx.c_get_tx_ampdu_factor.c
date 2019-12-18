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
typedef  int u8 ;
struct TYPE_2__ {int ampdu_factor; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; } ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static u8 get_tx_ampdu_factor(struct ieee80211_sta *sta)
{
	u8 exp = sta->ht_cap.ampdu_factor;

	/* the least ampdu factor is 8K, and the value in the tx desc is the
	 * max aggregation num, which represents val * 2 packets can be
	 * aggregated in an AMPDU, so here we should use 8/2=4 as the base
	 */
	return (BIT(2) << exp) - 1;
}