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
struct regmap_config {int val_bits; int reg_bits; scalar_t__ pad_bits; } ;

/* Variables and functions */
 int ENOTSUPP ; 

__attribute__((used)) static int regmap_sdw_config_check(const struct regmap_config *config)
{
	/* All register are 8-bits wide as per MIPI Soundwire 1.0 Spec */
	if (config->val_bits != 8)
		return -ENOTSUPP;

	/* Registers are 32 bits wide */
	if (config->reg_bits != 32)
		return -ENOTSUPP;

	if (config->pad_bits != 0)
		return -ENOTSUPP;

	return 0;
}