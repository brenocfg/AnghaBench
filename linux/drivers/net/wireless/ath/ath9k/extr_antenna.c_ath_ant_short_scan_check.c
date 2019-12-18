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
struct ath_ant_comb {int total_pkt_count; int alt_recv_cnt; int ant_ratio; scalar_t__ scan_start_time; int /*<<< orphan*/  alt_good; int /*<<< orphan*/  scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_ANT_DIV_COMB_SHORT_SCAN_INTR ; 
 int ATH_ANT_DIV_COMB_SHORT_SCAN_PKTCOUNT ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool ath_ant_short_scan_check(struct ath_ant_comb *antcomb)
{
	int alt_ratio;

	if (!antcomb->scan || !antcomb->alt_good)
		return false;

	if (time_after(jiffies, antcomb->scan_start_time +
		       msecs_to_jiffies(ATH_ANT_DIV_COMB_SHORT_SCAN_INTR)))
		return true;

	if (antcomb->total_pkt_count == ATH_ANT_DIV_COMB_SHORT_SCAN_PKTCOUNT) {
		alt_ratio = ((antcomb->alt_recv_cnt * 100) /
			     antcomb->total_pkt_count);
		if (alt_ratio < antcomb->ant_ratio)
			return true;
	}

	return false;
}