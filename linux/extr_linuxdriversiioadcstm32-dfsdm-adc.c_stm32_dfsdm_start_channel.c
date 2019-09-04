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
 int /*<<< orphan*/  DFSDM_CHCFGR1 (unsigned int) ; 
 int /*<<< orphan*/  DFSDM_CHCFGR1_CHEN (int) ; 
 int /*<<< orphan*/  DFSDM_CHCFGR1_CHEN_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_dfsdm_start_channel(struct stm32_dfsdm *dfsdm,
				     unsigned int ch_id)
{
	return regmap_update_bits(dfsdm->regmap, DFSDM_CHCFGR1(ch_id),
				  DFSDM_CHCFGR1_CHEN_MASK,
				  DFSDM_CHCFGR1_CHEN(1));
}