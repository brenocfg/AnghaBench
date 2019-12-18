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
struct stm32_dfsdm_channel {unsigned int id; int /*<<< orphan*/  alt_si; int /*<<< orphan*/  src; int /*<<< orphan*/  type; } ;
struct stm32_dfsdm {struct regmap* regmap; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_CHCFGR1 (unsigned int) ; 
 int /*<<< orphan*/  DFSDM_CHCFGR1_CHINSEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_CHCFGR1_CHINSEL_MASK ; 
 int /*<<< orphan*/  DFSDM_CHCFGR1_SITP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_CHCFGR1_SITP_MASK ; 
 int /*<<< orphan*/  DFSDM_CHCFGR1_SPICKSEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_CHCFGR1_SPICKSEL_MASK ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_dfsdm_chan_configure(struct stm32_dfsdm *dfsdm,
				      struct stm32_dfsdm_channel *ch)
{
	unsigned int id = ch->id;
	struct regmap *regmap = dfsdm->regmap;
	int ret;

	ret = regmap_update_bits(regmap, DFSDM_CHCFGR1(id),
				 DFSDM_CHCFGR1_SITP_MASK,
				 DFSDM_CHCFGR1_SITP(ch->type));
	if (ret < 0)
		return ret;
	ret = regmap_update_bits(regmap, DFSDM_CHCFGR1(id),
				 DFSDM_CHCFGR1_SPICKSEL_MASK,
				 DFSDM_CHCFGR1_SPICKSEL(ch->src));
	if (ret < 0)
		return ret;
	return regmap_update_bits(regmap, DFSDM_CHCFGR1(id),
				  DFSDM_CHCFGR1_CHINSEL_MASK,
				  DFSDM_CHCFGR1_CHINSEL(ch->alt_si));
}