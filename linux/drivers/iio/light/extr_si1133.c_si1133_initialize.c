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
struct si1133_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI1133_IRQ_CHANNEL_ENABLE ; 
 int /*<<< orphan*/  SI1133_REG_IRQ_ENABLE ; 
 int /*<<< orphan*/  SI1133_REG_MEAS_RATE ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si1133_cmd_reset_sw (struct si1133_data*) ; 
 int si1133_init_lux_channels (struct si1133_data*) ; 
 int si1133_param_set (struct si1133_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si1133_initialize(struct si1133_data *data)
{
	int err;

	err = si1133_cmd_reset_sw(data);
	if (err)
		return err;

	/* Turn off autonomous mode */
	err = si1133_param_set(data, SI1133_REG_MEAS_RATE, 0);
	if (err)
		return err;

	err = si1133_init_lux_channels(data);
	if (err)
		return err;

	return regmap_write(data->regmap, SI1133_REG_IRQ_ENABLE,
			    SI1133_IRQ_CHANNEL_ENABLE);
}