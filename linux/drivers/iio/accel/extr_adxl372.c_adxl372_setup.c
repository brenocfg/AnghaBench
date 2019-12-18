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
struct adxl372_state {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADXL372_ACTIVITY ; 
 int /*<<< orphan*/  ADXL372_BW_3200HZ ; 
 int /*<<< orphan*/  ADXL372_DEVID ; 
 unsigned int ADXL372_DEVID_VAL ; 
 int /*<<< orphan*/  ADXL372_FULL_BW_MEASUREMENT ; 
 int /*<<< orphan*/  ADXL372_INACTIVITY ; 
 int /*<<< orphan*/  ADXL372_LOOPED ; 
 int /*<<< orphan*/  ADXL372_ODR_6400HZ ; 
 int /*<<< orphan*/  ADXL372_RESET ; 
 int /*<<< orphan*/  ADXL372_RESET_CODE ; 
 int /*<<< orphan*/  ADXL372_STANDBY ; 
 int ENODEV ; 
 int adxl372_set_act_proc_mode (struct adxl372_state*,int /*<<< orphan*/ ) ; 
 int adxl372_set_activity_threshold (struct adxl372_state*,int /*<<< orphan*/ ,int,int,int) ; 
 int adxl372_set_activity_time_ms (struct adxl372_state*,int) ; 
 int adxl372_set_bandwidth (struct adxl372_state*,int /*<<< orphan*/ ) ; 
 int adxl372_set_inactivity_time_ms (struct adxl372_state*,int) ; 
 int adxl372_set_odr (struct adxl372_state*,int /*<<< orphan*/ ) ; 
 int adxl372_set_op_mode (struct adxl372_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adxl372_setup(struct adxl372_state *st)
{
	unsigned int regval;
	int ret;

	ret = regmap_read(st->regmap, ADXL372_DEVID, &regval);
	if (ret < 0)
		return ret;

	if (regval != ADXL372_DEVID_VAL) {
		dev_err(st->dev, "Invalid chip id %x\n", regval);
		return -ENODEV;
	}

	/*
	 * Perform a software reset to make sure the device is in a consistent
	 * state after start up.
	 */
	ret = regmap_write(st->regmap, ADXL372_RESET, ADXL372_RESET_CODE);
	if (ret < 0)
		return ret;

	ret = adxl372_set_op_mode(st, ADXL372_STANDBY);
	if (ret < 0)
		return ret;

	/* Set threshold for activity detection to 1g */
	ret = adxl372_set_activity_threshold(st, ADXL372_ACTIVITY,
					     true, true, 1000);
	if (ret < 0)
		return ret;

	/* Set threshold for inactivity detection to 100mg */
	ret = adxl372_set_activity_threshold(st, ADXL372_INACTIVITY,
					     true, true, 100);
	if (ret < 0)
		return ret;

	/* Set activity processing in Looped mode */
	ret = adxl372_set_act_proc_mode(st, ADXL372_LOOPED);
	if (ret < 0)
		return ret;

	ret = adxl372_set_odr(st, ADXL372_ODR_6400HZ);
	if (ret < 0)
		return ret;

	ret = adxl372_set_bandwidth(st, ADXL372_BW_3200HZ);
	if (ret < 0)
		return ret;

	/* Set activity timer to 1ms */
	ret = adxl372_set_activity_time_ms(st, 1);
	if (ret < 0)
		return ret;

	/* Set inactivity timer to 10s */
	ret = adxl372_set_inactivity_time_ms(st, 10000);
	if (ret < 0)
		return ret;

	/* Set the mode of operation to full bandwidth measurement mode */
	return adxl372_set_op_mode(st, ADXL372_FULL_BW_MEASUREMENT);
}