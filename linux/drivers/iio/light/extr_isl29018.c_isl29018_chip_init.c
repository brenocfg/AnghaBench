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
struct TYPE_2__ {int /*<<< orphan*/  uscale; int /*<<< orphan*/  scale; } ;
struct isl29018_chip {size_t type; size_t int_time; TYPE_1__ scale; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ISL29018_REG_ADD_COMMAND1 ; 
 int /*<<< orphan*/  ISL29018_REG_TEST ; 
 int /*<<< orphan*/  ISL29035_BOUT_MASK ; 
 unsigned int ISL29035_DEVICE_ID ; 
 unsigned int ISL29035_DEVICE_ID_MASK ; 
 unsigned int ISL29035_DEVICE_ID_SHIFT ; 
 int /*<<< orphan*/  ISL29035_REG_DEVICE_ID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/ ** isl29018_int_utimes ; 
 int isl29018_set_integration_time (struct isl29018_chip*,int /*<<< orphan*/ ) ; 
 int isl29018_set_scale (struct isl29018_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t isl29035 ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int isl29018_chip_init(struct isl29018_chip *chip)
{
	int status;
	struct device *dev = regmap_get_device(chip->regmap);

	if (chip->type == isl29035) {
		unsigned int id;

		status = regmap_read(chip->regmap, ISL29035_REG_DEVICE_ID, &id);
		if (status < 0) {
			dev_err(dev,
				"Error reading ID register with error %d\n",
				status);
			return status;
		}

		id = (id & ISL29035_DEVICE_ID_MASK) >> ISL29035_DEVICE_ID_SHIFT;

		if (id != ISL29035_DEVICE_ID)
			return -ENODEV;

		/* Clear brownout bit */
		status = regmap_update_bits(chip->regmap,
					    ISL29035_REG_DEVICE_ID,
					    ISL29035_BOUT_MASK, 0);
		if (status < 0)
			return status;
	}

	/*
	 * Code added per Intersil Application Note 1534:
	 *     When VDD sinks to approximately 1.8V or below, some of
	 * the part's registers may change their state. When VDD
	 * recovers to 2.25V (or greater), the part may thus be in an
	 * unknown mode of operation. The user can return the part to
	 * a known mode of operation either by (a) setting VDD = 0V for
	 * 1 second or more and then powering back up with a slew rate
	 * of 0.5V/ms or greater, or (b) via I2C disable all ALS/PROX
	 * conversions, clear the test registers, and then rewrite all
	 * registers to the desired values.
	 * ...
	 * For ISL29011, ISL29018, ISL29021, ISL29023
	 * 1. Write 0x00 to register 0x08 (TEST)
	 * 2. Write 0x00 to register 0x00 (CMD1)
	 * 3. Rewrite all registers to the desired values
	 *
	 * ISL29018 Data Sheet (FN6619.1, Feb 11, 2010) essentially says
	 * the same thing EXCEPT the data sheet asks for a 1ms delay after
	 * writing the CMD1 register.
	 */
	status = regmap_write(chip->regmap, ISL29018_REG_TEST, 0x0);
	if (status < 0) {
		dev_err(dev, "Failed to clear isl29018 TEST reg.(%d)\n",
			status);
		return status;
	}

	/*
	 * See Intersil AN1534 comments above.
	 * "Operating Mode" (COMMAND1) register is reprogrammed when
	 * data is read from the device.
	 */
	status = regmap_write(chip->regmap, ISL29018_REG_ADD_COMMAND1, 0);
	if (status < 0) {
		dev_err(dev, "Failed to clear isl29018 CMD1 reg.(%d)\n",
			status);
		return status;
	}

	usleep_range(1000, 2000);	/* per data sheet, page 10 */

	/* Set defaults */
	status = isl29018_set_scale(chip, chip->scale.scale,
				    chip->scale.uscale);
	if (status < 0) {
		dev_err(dev, "Init of isl29018 fails\n");
		return status;
	}

	status = isl29018_set_integration_time(chip,
			isl29018_int_utimes[chip->type][chip->int_time]);
	if (status < 0)
		dev_err(dev, "Init of isl29018 fails\n");

	return status;
}