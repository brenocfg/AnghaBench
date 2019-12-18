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
struct ath_softc {int dummy; } ;
struct ath_hw_antcomb_conf {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void ath9k_debug_stat_ant(struct ath_softc *sc,
					struct ath_hw_antcomb_conf *div_ant_conf,
					int main_rssi_avg, int alt_rssi_avg)
{

}