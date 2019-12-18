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
struct ar5416AniState {scalar_t__ ofdmNoiseImmunityLevel; scalar_t__ cckNoiseImmunityLevel; scalar_t__ ofdmsTurn; } ;
struct ath_hw {struct ar5416AniState ani; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_hw_set_cck_nil (struct ath_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  ath9k_hw_set_ofdm_nil (struct ath_hw*,scalar_t__,int) ; 

__attribute__((used)) static void ath9k_hw_ani_lower_immunity(struct ath_hw *ah)
{
	struct ar5416AniState *aniState = &ah->ani;

	/* lower OFDM noise immunity */
	if (aniState->ofdmNoiseImmunityLevel > 0 &&
	    (aniState->ofdmsTurn || aniState->cckNoiseImmunityLevel == 0)) {
		ath9k_hw_set_ofdm_nil(ah, aniState->ofdmNoiseImmunityLevel - 1,
				      false);
		return;
	}

	/* lower CCK noise immunity */
	if (aniState->cckNoiseImmunityLevel > 0)
		ath9k_hw_set_cck_nil(ah, aniState->cckNoiseImmunityLevel - 1,
				     false);
}