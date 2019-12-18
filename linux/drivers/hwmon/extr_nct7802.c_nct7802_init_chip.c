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
struct nct7802_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MODE ; 
 int /*<<< orphan*/  REG_START ; 
 int /*<<< orphan*/  REG_VMON_ENABLE ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int nct7802_init_chip(struct nct7802_data *data)
{
	int err;

	/* Enable ADC */
	err = regmap_update_bits(data->regmap, REG_START, 0x01, 0x01);
	if (err)
		return err;

	/* Enable local temperature sensor */
	err = regmap_update_bits(data->regmap, REG_MODE, 0x40, 0x40);
	if (err)
		return err;

	/* Enable Vcore and VCC voltage monitoring */
	return regmap_update_bits(data->regmap, REG_VMON_ENABLE, 0x03, 0x03);
}