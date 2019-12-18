#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u32 ;
struct il_priv {int const tx_power_user_lmt; } ;
struct il_channel_info {int scan_power; TYPE_1__* power_info; struct il3945_scan_power_info* scan_pwr_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  dsp_atten; int /*<<< orphan*/  tx_gain; } ;
struct il3945_scan_power_info {int requested_power; size_t power_table_idx; TYPE_2__ tpc; } ;
typedef  int s8 ;
typedef  size_t s32 ;
struct TYPE_6__ {int /*<<< orphan*/  dsp_atten; int /*<<< orphan*/  tx_gain; } ;
struct TYPE_4__ {size_t power_table_idx; int requested_power; } ;

/* Variables and functions */
 size_t RATE_6M_IDX_TBL ; 
 size_t il3945_hw_reg_fix_power_idx (size_t) ; 
 int min (int,int const) ; 
 TYPE_3__** power_gain_table ; 

__attribute__((used)) static void
il3945_hw_reg_set_scan_power(struct il_priv *il, u32 scan_tbl_idx, s32 rate_idx,
			     const s8 *clip_pwrs,
			     struct il_channel_info *ch_info, int band_idx)
{
	struct il3945_scan_power_info *scan_power_info;
	s8 power;
	u8 power_idx;

	scan_power_info = &ch_info->scan_pwr_info[scan_tbl_idx];

	/* use this channel group's 6Mbit clipping/saturation pwr,
	 *   but cap at regulatory scan power restriction (set during init
	 *   based on eeprom channel data) for this channel.  */
	power = min(ch_info->scan_power, clip_pwrs[RATE_6M_IDX_TBL]);

	power = min(power, il->tx_power_user_lmt);
	scan_power_info->requested_power = power;

	/* find difference between new scan *power* and current "normal"
	 *   Tx *power* for 6Mb.  Use this difference (x2) to adjust the
	 *   current "normal" temperature-compensated Tx power *idx* for
	 *   this rate (1Mb or 6Mb) to yield new temp-compensated scan power
	 *   *idx*. */
	power_idx =
	    ch_info->power_info[rate_idx].power_table_idx - (power -
							     ch_info->
							     power_info
							     [RATE_6M_IDX_TBL].
							     requested_power) *
	    2;

	/* store reference idx that we use when adjusting *all* scan
	 *   powers.  So we can accommodate user (all channel) or spectrum
	 *   management (single channel) power changes "between" temperature
	 *   feedback compensation procedures.
	 * don't force fit this reference idx into gain table; it may be a
	 *   negative number.  This will help avoid errors when we're at
	 *   the lower bounds (highest gains, for warmest temperatures)
	 *   of the table. */

	/* don't exceed table bounds for "real" setting */
	power_idx = il3945_hw_reg_fix_power_idx(power_idx);

	scan_power_info->power_table_idx = power_idx;
	scan_power_info->tpc.tx_gain =
	    power_gain_table[band_idx][power_idx].tx_gain;
	scan_power_info->tpc.dsp_atten =
	    power_gain_table[band_idx][power_idx].dsp_atten;
}