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
struct regmap {int dummy; } ;
struct max17042_config_data {int /*<<< orphan*/  full_soc_thresh; int /*<<< orphan*/  relax_cfg; int /*<<< orphan*/  filter_cfg; int /*<<< orphan*/  learn_cfg; int /*<<< orphan*/  config; } ;
struct max17042_chip {scalar_t__ chip_type; struct regmap* regmap; TYPE_1__* pdata; } ;
struct TYPE_2__ {struct max17042_config_data* config_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX17042_CONFIG ; 
 int /*<<< orphan*/  MAX17042_FilterCFG ; 
 int /*<<< orphan*/  MAX17042_LearnCFG ; 
 int /*<<< orphan*/  MAX17042_RelaxCFG ; 
 int /*<<< orphan*/  MAX17047_FullSOCThr ; 
 scalar_t__ MAXIM_DEVICE_TYPE_MAX17047 ; 
 scalar_t__ MAXIM_DEVICE_TYPE_MAX17050 ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max17042_write_config_regs(struct max17042_chip *chip)
{
	struct max17042_config_data *config = chip->pdata->config_data;
	struct regmap *map = chip->regmap;

	regmap_write(map, MAX17042_CONFIG, config->config);
	regmap_write(map, MAX17042_LearnCFG, config->learn_cfg);
	regmap_write(map, MAX17042_FilterCFG,
			config->filter_cfg);
	regmap_write(map, MAX17042_RelaxCFG, config->relax_cfg);
	if (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17047 ||
			chip->chip_type == MAXIM_DEVICE_TYPE_MAX17050)
		regmap_write(map, MAX17047_FullSOCThr,
						config->full_soc_thresh);
}