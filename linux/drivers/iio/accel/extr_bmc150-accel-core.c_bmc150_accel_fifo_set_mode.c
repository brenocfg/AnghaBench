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
struct device {int dummy; } ;
struct bmc150_accel_data {int /*<<< orphan*/  watermark; int /*<<< orphan*/  regmap; int /*<<< orphan*/  fifo_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_ACCEL_REG_FIFO_CONFIG0 ; 
 int /*<<< orphan*/  BMC150_ACCEL_REG_FIFO_CONFIG1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmc150_accel_fifo_set_mode(struct bmc150_accel_data *data)
{
	struct device *dev = regmap_get_device(data->regmap);
	u8 reg = BMC150_ACCEL_REG_FIFO_CONFIG1;
	int ret;

	ret = regmap_write(data->regmap, reg, data->fifo_mode);
	if (ret < 0) {
		dev_err(dev, "Error writing reg_fifo_config1\n");
		return ret;
	}

	if (!data->fifo_mode)
		return 0;

	ret = regmap_write(data->regmap, BMC150_ACCEL_REG_FIFO_CONFIG0,
			   data->watermark);
	if (ret < 0)
		dev_err(dev, "Error writing reg_fifo_config0\n");

	return ret;
}