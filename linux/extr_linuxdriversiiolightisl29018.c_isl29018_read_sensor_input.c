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
 int ISL29018_CMD1_OPMODE_SHIFT ; 
 int /*<<< orphan*/  ISL29018_CONV_TIME_MS ; 
 int /*<<< orphan*/  ISL29018_REG_ADD_COMMAND1 ; 
 int /*<<< orphan*/  ISL29018_REG_ADD_DATA_LSB ; 
 int /*<<< orphan*/  ISL29018_REG_ADD_DATA_MSB ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isl29018_read_sensor_input(struct isl29018_chip *chip, int mode)
{
	int status;
	unsigned int lsb;
	unsigned int msb;
	struct device *dev = regmap_get_device(chip->regmap);

	/* Set mode */
	status = regmap_write(chip->regmap, ISL29018_REG_ADD_COMMAND1,
			      mode << ISL29018_CMD1_OPMODE_SHIFT);
	if (status) {
		dev_err(dev,
			"Error in setting operating mode err %d\n", status);
		return status;
	}
	msleep(ISL29018_CONV_TIME_MS);
	status = regmap_read(chip->regmap, ISL29018_REG_ADD_DATA_LSB, &lsb);
	if (status < 0) {
		dev_err(dev,
			"Error in reading LSB DATA with err %d\n", status);
		return status;
	}

	status = regmap_read(chip->regmap, ISL29018_REG_ADD_DATA_MSB, &msb);
	if (status < 0) {
		dev_err(dev,
			"Error in reading MSB DATA with error %d\n", status);
		return status;
	}
	dev_vdbg(dev, "MSB 0x%x and LSB 0x%x\n", msb, lsb);

	return (msb << 8) | lsb;
}