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
struct ar5416AniState {scalar_t__ cckNoiseImmunityLevel; } ;
struct ath_hw {struct ar5416AniState ani; } ;

/* Variables and functions */
 scalar_t__ ATH9K_ANI_CCK_MAX_LEVEL ; 
 int /*<<< orphan*/  ath9k_hw_set_cck_nil (struct ath_hw*,scalar_t__,int) ; 

__attribute__((used)) static void ath9k_hw_ani_cck_err_trigger(struct ath_hw *ah)
{
	struct ar5416AniState *aniState = &ah->ani;

	if (aniState->cckNoiseImmunityLevel < ATH9K_ANI_CCK_MAX_LEVEL)
		ath9k_hw_set_cck_nil(ah, aniState->cckNoiseImmunityLevel + 1,
				     false);
}