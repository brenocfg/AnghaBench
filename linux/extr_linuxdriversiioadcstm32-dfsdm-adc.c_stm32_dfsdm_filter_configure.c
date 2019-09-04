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
struct stm32_dfsdm_filter {int /*<<< orphan*/  sync_mode; int /*<<< orphan*/  ford; scalar_t__ fosr; scalar_t__ iosr; } ;
struct stm32_dfsdm {struct stm32_dfsdm_filter* fl_list; struct regmap* regmap; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_CR1 (unsigned int) ; 
 int /*<<< orphan*/  DFSDM_CR1_RCH (unsigned int) ; 
 int /*<<< orphan*/  DFSDM_CR1_RCH_MASK ; 
 int /*<<< orphan*/  DFSDM_CR1_RSYNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_CR1_RSYNC_MASK ; 
 int /*<<< orphan*/  DFSDM_FCR (unsigned int) ; 
 int /*<<< orphan*/  DFSDM_FCR_FORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_FCR_FORD_MASK ; 
 int /*<<< orphan*/  DFSDM_FCR_FOSR (scalar_t__) ; 
 int /*<<< orphan*/  DFSDM_FCR_FOSR_MASK ; 
 int /*<<< orphan*/  DFSDM_FCR_IOSR (scalar_t__) ; 
 int /*<<< orphan*/  DFSDM_FCR_IOSR_MASK ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_dfsdm_filter_configure(struct stm32_dfsdm *dfsdm,
					unsigned int fl_id, unsigned int ch_id)
{
	struct regmap *regmap = dfsdm->regmap;
	struct stm32_dfsdm_filter *fl = &dfsdm->fl_list[fl_id];
	int ret;

	/* Average integrator oversampling */
	ret = regmap_update_bits(regmap, DFSDM_FCR(fl_id), DFSDM_FCR_IOSR_MASK,
				 DFSDM_FCR_IOSR(fl->iosr - 1));
	if (ret)
		return ret;

	/* Filter order and Oversampling */
	ret = regmap_update_bits(regmap, DFSDM_FCR(fl_id), DFSDM_FCR_FOSR_MASK,
				 DFSDM_FCR_FOSR(fl->fosr - 1));
	if (ret)
		return ret;

	ret = regmap_update_bits(regmap, DFSDM_FCR(fl_id), DFSDM_FCR_FORD_MASK,
				 DFSDM_FCR_FORD(fl->ford));
	if (ret)
		return ret;

	/* No scan mode supported for the moment */
	ret = regmap_update_bits(regmap, DFSDM_CR1(fl_id), DFSDM_CR1_RCH_MASK,
				 DFSDM_CR1_RCH(ch_id));
	if (ret)
		return ret;

	return regmap_update_bits(regmap, DFSDM_CR1(fl_id),
				  DFSDM_CR1_RSYNC_MASK,
				  DFSDM_CR1_RSYNC(fl->sync_mode));
}