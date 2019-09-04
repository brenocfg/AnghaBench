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
typedef  int u8 ;
typedef  int u32 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int PLL_BIAS_COUNT_MASK ; 
 int PLL_BIAS_COUNT_SHIFT ; 
 int PLL_LOCK_COUNT_MASK ; 
 int PLL_LOCK_COUNT_SHIFT ; 
 int PLL_VOTE_FSM_ENA ; 
 int PLL_VOTE_FSM_RESET ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int,int,int) ; 

void
qcom_pll_set_fsm_mode(struct regmap *map, u32 reg, u8 bias_count, u8 lock_count)
{
	u32 val;
	u32 mask;

	/* De-assert reset to FSM */
	regmap_update_bits(map, reg, PLL_VOTE_FSM_RESET, 0);

	/* Program bias count and lock count */
	val = bias_count << PLL_BIAS_COUNT_SHIFT |
		lock_count << PLL_LOCK_COUNT_SHIFT;
	mask = PLL_BIAS_COUNT_MASK << PLL_BIAS_COUNT_SHIFT;
	mask |= PLL_LOCK_COUNT_MASK << PLL_LOCK_COUNT_SHIFT;
	regmap_update_bits(map, reg, mask, val);

	/* Enable PLL FSM voting */
	regmap_update_bits(map, reg, PLL_VOTE_FSM_ENA, PLL_VOTE_FSM_ENA);
}