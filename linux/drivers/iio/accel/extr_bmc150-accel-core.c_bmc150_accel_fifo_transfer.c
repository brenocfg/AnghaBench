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
struct device {int dummy; } ;
struct bmc150_accel_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_ACCEL_REG_FIFO_DATA ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_raw_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bmc150_accel_fifo_transfer(struct bmc150_accel_data *data,
				      char *buffer, int samples)
{
	struct device *dev = regmap_get_device(data->regmap);
	int sample_length = 3 * 2;
	int ret;
	int total_length = samples * sample_length;

	ret = regmap_raw_read(data->regmap, BMC150_ACCEL_REG_FIFO_DATA,
			      buffer, total_length);
	if (ret)
		dev_err(dev,
			"Error transferring data from fifo: %d\n", ret);

	return ret;
}