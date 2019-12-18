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
struct atmel_smc_cs_conf {int /*<<< orphan*/  mode; int /*<<< orphan*/  cycle; int /*<<< orphan*/  pulse; int /*<<< orphan*/  setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_SMC_CYCLE (int) ; 
 int /*<<< orphan*/  ATMEL_SMC_MODE (int) ; 
 int /*<<< orphan*/  ATMEL_SMC_PULSE (int) ; 
 int /*<<< orphan*/  ATMEL_SMC_SETUP (int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void atmel_smc_cs_conf_apply(struct regmap *regmap, int cs,
			     const struct atmel_smc_cs_conf *conf)
{
	regmap_write(regmap, ATMEL_SMC_SETUP(cs), conf->setup);
	regmap_write(regmap, ATMEL_SMC_PULSE(cs), conf->pulse);
	regmap_write(regmap, ATMEL_SMC_CYCLE(cs), conf->cycle);
	regmap_write(regmap, ATMEL_SMC_MODE(cs), conf->mode);
}