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
struct isl29018_chip {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISL29018_CMD1_OPMODE_IR_ONCE ; 
 int /*<<< orphan*/  ISL29018_CMD1_OPMODE_PROX_ONCE ; 
 int /*<<< orphan*/  ISL29018_CMD2_SCHEME_MASK ; 
 int ISL29018_CMD2_SCHEME_SHIFT ; 
 int /*<<< orphan*/  ISL29018_REG_ADD_COMMAND2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int isl29018_read_sensor_input (struct isl29018_chip*,int /*<<< orphan*/ ) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isl29018_read_proximity_ir(struct isl29018_chip *chip, int scheme,
				      int *near_ir)
{
	int status;
	int prox_data = -1;
	int ir_data = -1;
	struct device *dev = regmap_get_device(chip->regmap);

	/* Do proximity sensing with required scheme */
	status = regmap_update_bits(chip->regmap, ISL29018_REG_ADD_COMMAND2,
				    ISL29018_CMD2_SCHEME_MASK,
				    scheme << ISL29018_CMD2_SCHEME_SHIFT);
	if (status) {
		dev_err(dev, "Error in setting operating mode\n");
		return status;
	}

	prox_data = isl29018_read_sensor_input(chip,
					       ISL29018_CMD1_OPMODE_PROX_ONCE);
	if (prox_data < 0)
		return prox_data;

	if (scheme == 1) {
		*near_ir = prox_data;
		return 0;
	}

	ir_data = isl29018_read_sensor_input(chip,
					     ISL29018_CMD1_OPMODE_IR_ONCE);
	if (ir_data < 0)
		return ir_data;

	if (prox_data >= ir_data)
		*near_ir = prox_data - ir_data;
	else
		*near_ir = 0;

	return 0;
}