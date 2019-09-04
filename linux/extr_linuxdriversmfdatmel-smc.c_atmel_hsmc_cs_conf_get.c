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
struct regmap {int dummy; } ;
struct atmel_smc_cs_conf {int /*<<< orphan*/  mode; int /*<<< orphan*/  timings; int /*<<< orphan*/  cycle; int /*<<< orphan*/  pulse; int /*<<< orphan*/  setup; } ;
struct atmel_hsmc_reg_layout {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HSMC_CYCLE (struct atmel_hsmc_reg_layout const*,int) ; 
 int /*<<< orphan*/  ATMEL_HSMC_MODE (struct atmel_hsmc_reg_layout const*,int) ; 
 int /*<<< orphan*/  ATMEL_HSMC_PULSE (struct atmel_hsmc_reg_layout const*,int) ; 
 int /*<<< orphan*/  ATMEL_HSMC_SETUP (struct atmel_hsmc_reg_layout const*,int) ; 
 int /*<<< orphan*/  ATMEL_HSMC_TIMINGS (struct atmel_hsmc_reg_layout const*,int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void atmel_hsmc_cs_conf_get(struct regmap *regmap,
			    const struct atmel_hsmc_reg_layout *layout,
			    int cs, struct atmel_smc_cs_conf *conf)
{
	regmap_read(regmap, ATMEL_HSMC_SETUP(layout, cs), &conf->setup);
	regmap_read(regmap, ATMEL_HSMC_PULSE(layout, cs), &conf->pulse);
	regmap_read(regmap, ATMEL_HSMC_CYCLE(layout, cs), &conf->cycle);
	regmap_read(regmap, ATMEL_HSMC_TIMINGS(layout, cs), &conf->timings);
	regmap_read(regmap, ATMEL_HSMC_MODE(layout, cs), &conf->mode);
}