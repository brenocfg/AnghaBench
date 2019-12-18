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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ak8975_data {TYPE_1__* def; int /*<<< orphan*/  eoc_gpio; scalar_t__ eoc_irq; } ;
struct TYPE_2__ {int* ctrl_masks; int /*<<< orphan*/ * ctrl_regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MODE_ONCE ; 
 size_t ST1_DRDY ; 
 size_t ST2 ; 
 size_t ST2_DERR ; 
 size_t ST2_HOFL ; 
 int ak8975_set_mode (struct ak8975_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client const*,int /*<<< orphan*/ ) ; 
 int wait_conversion_complete_gpio (struct ak8975_data*) ; 
 int wait_conversion_complete_interrupt (struct ak8975_data*) ; 
 int wait_conversion_complete_polled (struct ak8975_data*) ; 

__attribute__((used)) static int ak8975_start_read_axis(struct ak8975_data *data,
				  const struct i2c_client *client)
{
	/* Set up the device for taking a sample. */
	int ret = ak8975_set_mode(data, MODE_ONCE);

	if (ret < 0) {
		dev_err(&client->dev, "Error in setting operating mode\n");
		return ret;
	}

	/* Wait for the conversion to complete. */
	if (data->eoc_irq)
		ret = wait_conversion_complete_interrupt(data);
	else if (gpio_is_valid(data->eoc_gpio))
		ret = wait_conversion_complete_gpio(data);
	else
		ret = wait_conversion_complete_polled(data);
	if (ret < 0)
		return ret;

	/* This will be executed only for non-interrupt based waiting case */
	if (ret & data->def->ctrl_masks[ST1_DRDY]) {
		ret = i2c_smbus_read_byte_data(client,
					       data->def->ctrl_regs[ST2]);
		if (ret < 0) {
			dev_err(&client->dev, "Error in reading ST2\n");
			return ret;
		}
		if (ret & (data->def->ctrl_masks[ST2_DERR] |
			   data->def->ctrl_masks[ST2_HOFL])) {
			dev_err(&client->dev, "ST2 status error 0x%x\n", ret);
			return -EINVAL;
		}
	}

	return 0;
}