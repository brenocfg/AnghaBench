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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct ina3221_input {int shunt_resistor; } ;
struct ina3221_data {int /*<<< orphan*/  regmap; struct ina3221_input* inputs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int INT_MAX ; 
 int INT_MIN ; 
 int clamp_val (int,int,int) ; 
 struct ina3221_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ ** ina3221_curr_reg ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ina3221_write_curr(struct device *dev, u32 attr,
			      int channel, long val)
{
	struct ina3221_data *ina = dev_get_drvdata(dev);
	struct ina3221_input *input = &ina->inputs[channel];
	int resistance_uo = input->shunt_resistor;
	u8 reg = ina3221_curr_reg[attr][channel];
	int regval, current_ma, voltage_uv;

	/* clamp current */
	current_ma = clamp_val(val,
			       INT_MIN / resistance_uo,
			       INT_MAX / resistance_uo);

	voltage_uv = DIV_ROUND_CLOSEST(current_ma * resistance_uo, 1000);

	/* clamp voltage */
	voltage_uv = clamp_val(voltage_uv, -163800, 163800);

	/* 1 / 40uV(scale) << 3(register shift) = 5 */
	regval = DIV_ROUND_CLOSEST(voltage_uv, 5) & 0xfff8;

	return regmap_write(ina->regmap, reg, regval);
}