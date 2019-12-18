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
struct pulse_event {int dummy; } ;
struct dfs_pattern_detector {int /*<<< orphan*/  (* add_pulse ) (struct dfs_pattern_detector*,struct pulse_event*,int /*<<< orphan*/ *) ;} ;
struct ath_softc {int /*<<< orphan*/  hw; struct dfs_pattern_detector* dfs_detector; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFS_STAT_INC (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_radar_detected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulses_processed ; 
 int /*<<< orphan*/  radar_detected ; 
 int /*<<< orphan*/  stub1 (struct dfs_pattern_detector*,struct pulse_event*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath9k_dfs_process_radar_pulse(struct ath_softc *sc, struct pulse_event *pe)
{
	struct dfs_pattern_detector *pd = sc->dfs_detector;
	DFS_STAT_INC(sc, pulses_processed);
	if (pd == NULL)
		return;
	if (!pd->add_pulse(pd, pe, NULL))
		return;
	DFS_STAT_INC(sc, radar_detected);
	ieee80211_radar_detected(sc->hw);
}