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
struct TYPE_2__ {int noise_imm_level; } ;
struct ath5k_hw {TYPE_1__ ani_state; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_PHY_AGCCOARSE ; 
 int /*<<< orphan*/  AR5K_PHY_AGCCOARSE_HI ; 
 int /*<<< orphan*/  AR5K_PHY_AGCCOARSE_LO ; 
 int /*<<< orphan*/  AR5K_PHY_DESIRED_SIZE ; 
 int /*<<< orphan*/  AR5K_PHY_DESIRED_SIZE_TOT ; 
 int /*<<< orphan*/  AR5K_PHY_SIG ; 
 int /*<<< orphan*/  AR5K_PHY_SIG_FIRPWR ; 
 int /*<<< orphan*/  AR5K_REG_WRITE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  ATH5K_DBG_UNLIMIT (struct ath5k_hw*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_ANI ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*,int) ; 

void
ath5k_ani_set_noise_immunity_level(struct ath5k_hw *ah, int level)
{
	/* TODO:
	 * ANI documents suggest the following five levels to use, but the HAL
	 * and ath9k use only the last two levels, making this
	 * essentially an on/off option. There *may* be a reason for this (???),
	 * so i stick with the HAL version for now...
	 */
#if 0
	static const s8 lo[] = { -52, -56, -60, -64, -70 };
	static const s8 hi[] = { -18, -18, -16, -14, -12 };
	static const s8 sz[] = { -34, -41, -48, -55, -62 };
	static const s8 fr[] = { -70, -72, -75, -78, -80 };
#else
	static const s8 lo[] = { -64, -70 };
	static const s8 hi[] = { -14, -12 };
	static const s8 sz[] = { -55, -62 };
	static const s8 fr[] = { -78, -80 };
#endif
	if (level < 0 || level >= ARRAY_SIZE(sz)) {
		ATH5K_ERR(ah, "noise immunity level %d out of range",
			  level);
		return;
	}

	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_DESIRED_SIZE,
				AR5K_PHY_DESIRED_SIZE_TOT, sz[level]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_AGCCOARSE,
				AR5K_PHY_AGCCOARSE_LO, lo[level]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_AGCCOARSE,
				AR5K_PHY_AGCCOARSE_HI, hi[level]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_SIG,
				AR5K_PHY_SIG_FIRPWR, fr[level]);

	ah->ani_state.noise_imm_level = level;
	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "new level %d", level);
}