#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct ath_antenna_stats* ant_stats; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct ath_softc {TYPE_2__ debug; } ;
struct ath_hw_antcomb_conf {size_t main_lna_conf; size_t alt_lna_conf; } ;
struct ath_antenna_stats {int rssi_avg; int /*<<< orphan*/ * lna_attempt_cnt; } ;

/* Variables and functions */
 size_t ANT_ALT ; 
 size_t ANT_MAIN ; 

void ath9k_debug_stat_ant(struct ath_softc *sc,
			  struct ath_hw_antcomb_conf *div_ant_conf,
			  int main_rssi_avg, int alt_rssi_avg)
{
	struct ath_antenna_stats *as_main = &sc->debug.stats.ant_stats[ANT_MAIN];
	struct ath_antenna_stats *as_alt = &sc->debug.stats.ant_stats[ANT_ALT];

	as_main->lna_attempt_cnt[div_ant_conf->main_lna_conf]++;
	as_alt->lna_attempt_cnt[div_ant_conf->alt_lna_conf]++;

	as_main->rssi_avg = main_rssi_avg;
	as_alt->rssi_avg = alt_rssi_avg;
}