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
struct TYPE_2__ {size_t g_step_idx; int g_current; int g_high; int g_target; int g_low; } ;
struct ath5k_hw {int ah_radio; TYPE_1__ ah_gain; } ;
struct ath5k_gain_opt_step {int gos_gain; } ;
struct ath5k_gain_opt {int go_steps_count; struct ath5k_gain_opt_step* go_step; } ;
typedef  int s8 ;

/* Variables and functions */
#define  AR5K_RF5111 129 
#define  AR5K_RF5112 128 
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,int,size_t,int,int) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_CALIBRATE ; 
 struct ath5k_gain_opt rfgain_opt_5111 ; 
 struct ath5k_gain_opt rfgain_opt_5112 ; 

__attribute__((used)) static s8
ath5k_hw_rf_gainf_adjust(struct ath5k_hw *ah)
{
	const struct ath5k_gain_opt *go;
	const struct ath5k_gain_opt_step *g_step;
	int ret = 0;

	switch (ah->ah_radio) {
	case AR5K_RF5111:
		go = &rfgain_opt_5111;
		break;
	case AR5K_RF5112:
		go = &rfgain_opt_5112;
		break;
	default:
		return 0;
	}

	g_step = &go->go_step[ah->ah_gain.g_step_idx];

	if (ah->ah_gain.g_current >= ah->ah_gain.g_high) {

		/* Reached maximum */
		if (ah->ah_gain.g_step_idx == 0)
			return -1;

		for (ah->ah_gain.g_target = ah->ah_gain.g_current;
				ah->ah_gain.g_target >=  ah->ah_gain.g_high &&
				ah->ah_gain.g_step_idx > 0;
				g_step = &go->go_step[ah->ah_gain.g_step_idx])
			ah->ah_gain.g_target -= 2 *
			    (go->go_step[--(ah->ah_gain.g_step_idx)].gos_gain -
			    g_step->gos_gain);

		ret = 1;
		goto done;
	}

	if (ah->ah_gain.g_current <= ah->ah_gain.g_low) {

		/* Reached minimum */
		if (ah->ah_gain.g_step_idx == (go->go_steps_count - 1))
			return -2;

		for (ah->ah_gain.g_target = ah->ah_gain.g_current;
				ah->ah_gain.g_target <= ah->ah_gain.g_low &&
				ah->ah_gain.g_step_idx < go->go_steps_count - 1;
				g_step = &go->go_step[ah->ah_gain.g_step_idx])
			ah->ah_gain.g_target -= 2 *
			    (go->go_step[++ah->ah_gain.g_step_idx].gos_gain -
			    g_step->gos_gain);

		ret = 2;
		goto done;
	}

done:
	ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
		"ret %d, gain step %u, current gain %u, target gain %u\n",
		ret, ah->ah_gain.g_step_idx, ah->ah_gain.g_current,
		ah->ah_gain.g_target);

	return ret;
}