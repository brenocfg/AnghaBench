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
struct ath_hw {int /*<<< orphan*/ * tx_power; int /*<<< orphan*/ * tx_power_stbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9300_HT_DS_RATES ; 
 int /*<<< orphan*/  AR9300_HT_SS_RATES ; 
 int /*<<< orphan*/  AR9300_HT_TS_RATES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9003_hw_init_txpower_stbc(struct ath_hw *ah, int ss_offset,
					int ds_offset, int ts_offset)
{
	memcpy(&ah->tx_power_stbc[ss_offset], &ah->tx_power[ss_offset],
	       AR9300_HT_SS_RATES);
	memcpy(&ah->tx_power_stbc[ds_offset], &ah->tx_power[ds_offset],
	       AR9300_HT_DS_RATES);
	memcpy(&ah->tx_power_stbc[ts_offset], &ah->tx_power[ts_offset],
	       AR9300_HT_TS_RATES);
}