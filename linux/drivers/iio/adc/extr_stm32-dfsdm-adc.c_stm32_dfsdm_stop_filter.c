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
struct stm32_dfsdm {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_CR1 (unsigned int) ; 
 int /*<<< orphan*/  DFSDM_CR1_DFEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_CR1_DFEN_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_dfsdm_stop_filter(struct stm32_dfsdm *dfsdm,
				    unsigned int fl_id)
{
	/* Disable conversion */
	regmap_update_bits(dfsdm->regmap, DFSDM_CR1(fl_id),
			   DFSDM_CR1_DFEN_MASK, DFSDM_CR1_DFEN(0));
}