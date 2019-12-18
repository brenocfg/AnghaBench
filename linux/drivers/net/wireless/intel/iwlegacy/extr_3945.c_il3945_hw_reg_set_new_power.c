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
struct TYPE_4__ {TYPE_1__* clip_groups; } ;
struct il_priv {TYPE_2__ _3945; } ;
struct il_channel_info {size_t group_idx; struct il3945_channel_power_info* power_info; int /*<<< orphan*/  curr_txpow; } ;
struct il3945_channel_power_info {int requested_power; scalar_t__ base_power_idx; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_3__ {int /*<<< orphan*/ * clip_powers; } ;

/* Variables and functions */
 scalar_t__ IL_CCK_FROM_OFDM_IDX_DIFF ; 
 int IL_CCK_FROM_OFDM_POWER_DIFF ; 
 int RATE_11M_IDX_TBL ; 
 size_t RATE_12M_IDX_TBL ; 
 int RATE_1M_IDX_TBL ; 
 int RATE_54M_IDX_TBL ; 
 int RATE_6M_IDX_TBL ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
il3945_hw_reg_set_new_power(struct il_priv *il, struct il_channel_info *ch_info)
{
	struct il3945_channel_power_info *power_info;
	int power_changed = 0;
	int i;
	const s8 *clip_pwrs;
	int power;

	/* Get this chnlgrp's rate-to-max/clip-powers table */
	clip_pwrs = il->_3945.clip_groups[ch_info->group_idx].clip_powers;

	/* Get this channel's rate-to-current-power settings table */
	power_info = ch_info->power_info;

	/* update OFDM Txpower settings */
	for (i = RATE_6M_IDX_TBL; i <= RATE_54M_IDX_TBL; i++, ++power_info) {
		int delta_idx;

		/* limit new power to be no more than h/w capability */
		power = min(ch_info->curr_txpow, clip_pwrs[i]);
		if (power == power_info->requested_power)
			continue;

		/* find difference between old and new requested powers,
		 *    update base (non-temp-compensated) power idx */
		delta_idx = (power - power_info->requested_power) * 2;
		power_info->base_power_idx -= delta_idx;

		/* save new requested power value */
		power_info->requested_power = power;

		power_changed = 1;
	}

	/* update CCK Txpower settings, based on OFDM 12M setting ...
	 *    ... all CCK power settings for a given channel are the *same*. */
	if (power_changed) {
		power =
		    ch_info->power_info[RATE_12M_IDX_TBL].requested_power +
		    IL_CCK_FROM_OFDM_POWER_DIFF;

		/* do all CCK rates' il3945_channel_power_info structures */
		for (i = RATE_1M_IDX_TBL; i <= RATE_11M_IDX_TBL; i++) {
			power_info->requested_power = power;
			power_info->base_power_idx =
			    ch_info->power_info[RATE_12M_IDX_TBL].
			    base_power_idx + IL_CCK_FROM_OFDM_IDX_DIFF;
			++power_info;
		}
	}

	return 0;
}