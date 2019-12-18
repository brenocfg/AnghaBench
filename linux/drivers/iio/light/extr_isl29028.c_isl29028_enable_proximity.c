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
struct isl29028_chip {int /*<<< orphan*/  prox_sampling_frac; int /*<<< orphan*/  prox_sampling_int; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  sleep_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISL29028_CONF_PROX_EN ; 
 int /*<<< orphan*/  ISL29028_CONF_PROX_EN_MASK ; 
 int /*<<< orphan*/  ISL29028_REG_CONFIGURE ; 
 int isl29028_find_prox_sleep_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* isl29028_prox_data ; 
 int isl29028_set_proxim_sampling (struct isl29028_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isl29028_enable_proximity(struct isl29028_chip *chip)
{
	int prox_index, ret;

	ret = isl29028_set_proxim_sampling(chip, chip->prox_sampling_int,
					   chip->prox_sampling_frac);
	if (ret < 0)
		return ret;

	ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
				 ISL29028_CONF_PROX_EN_MASK,
				 ISL29028_CONF_PROX_EN);
	if (ret < 0)
		return ret;

	/* Wait for conversion to be complete for first sample */
	prox_index = isl29028_find_prox_sleep_index(chip->prox_sampling_int,
						    chip->prox_sampling_frac);
	if (prox_index < 0)
		return prox_index;

	msleep(isl29028_prox_data[prox_index].sleep_time);

	return 0;
}