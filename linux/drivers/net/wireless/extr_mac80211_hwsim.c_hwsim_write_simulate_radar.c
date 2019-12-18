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
typedef  int /*<<< orphan*/  u64 ;
struct mac80211_hwsim_data {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_radar_detected (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwsim_write_simulate_radar(void *dat, u64 val)
{
	struct mac80211_hwsim_data *data = dat;

	ieee80211_radar_detected(data->hw);

	return 0;
}