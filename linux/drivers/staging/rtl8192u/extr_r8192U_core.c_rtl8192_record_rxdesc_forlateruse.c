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
struct ieee80211_rx_stats {int /*<<< orphan*/  Seq_Num; int /*<<< orphan*/  bFirstMPDU; int /*<<< orphan*/  bIsAMPDU; } ;

/* Variables and functions */

__attribute__((used)) static void rtl8192_record_rxdesc_forlateruse(
		struct ieee80211_rx_stats *psrc_stats,
		struct ieee80211_rx_stats *ptarget_stats)
{
	ptarget_stats->bIsAMPDU = psrc_stats->bIsAMPDU;
	ptarget_stats->bFirstMPDU = psrc_stats->bFirstMPDU;
	ptarget_stats->Seq_Num = psrc_stats->Seq_Num;
}