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
struct ath5k_ani_state {scalar_t__ ani_mode; scalar_t__ ofdm_errors; scalar_t__ cck_errors; } ;
struct TYPE_2__ {int /*<<< orphan*/  cap_has_phyerr_counters; } ;
struct ath5k_hw {int /*<<< orphan*/  ani_tasklet; struct ath5k_ani_state ani_state; TYPE_1__ ah_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_CCK_FIL_CNT ; 
 int /*<<< orphan*/  AR5K_OFDM_FIL_CNT ; 
 scalar_t__ ATH5K_ANI_CCK_TRIG_HIGH ; 
 scalar_t__ ATH5K_ANI_MODE_AUTO ; 
 scalar_t__ ATH5K_ANI_OFDM_TRIG_HIGH ; 
 scalar_t__ ath5k_ani_save_and_clear_phy_errors (struct ath5k_hw*,struct ath5k_ani_state*) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void
ath5k_ani_mib_intr(struct ath5k_hw *ah)
{
	struct ath5k_ani_state *as = &ah->ani_state;

	/* nothing to do here if HW does not have PHY error counters - they
	 * can't be the reason for the MIB interrupt then */
	if (!ah->ah_capabilities.cap_has_phyerr_counters)
		return;

	/* not in use but clear anyways */
	ath5k_hw_reg_write(ah, 0, AR5K_OFDM_FIL_CNT);
	ath5k_hw_reg_write(ah, 0, AR5K_CCK_FIL_CNT);

	if (ah->ani_state.ani_mode != ATH5K_ANI_MODE_AUTO)
		return;

	/* If one of the errors triggered, we can get a superfluous second
	 * interrupt, even though we have already reset the register. The
	 * function detects that so we can return early. */
	if (ath5k_ani_save_and_clear_phy_errors(ah, as) == 0)
		return;

	if (as->ofdm_errors > ATH5K_ANI_OFDM_TRIG_HIGH ||
	    as->cck_errors > ATH5K_ANI_CCK_TRIG_HIGH)
		tasklet_schedule(&ah->ani_tasklet);
}