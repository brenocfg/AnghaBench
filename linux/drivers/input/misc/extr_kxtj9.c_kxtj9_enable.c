#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  g_range; } ;
struct kxtj9_data {TYPE_2__* client; int /*<<< orphan*/  last_poll_interval; int /*<<< orphan*/  ctrl_reg1; TYPE_1__ pdata; int /*<<< orphan*/  int_ctrl; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_REG1 ; 
 int /*<<< orphan*/  INT_CTRL1 ; 
 int /*<<< orphan*/  INT_REL ; 
 int /*<<< orphan*/  PC1_ON ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte_data (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxtj9_device_power_off (struct kxtj9_data*) ; 
 int kxtj9_device_power_on (struct kxtj9_data*) ; 
 int kxtj9_update_g_range (struct kxtj9_data*,int /*<<< orphan*/ ) ; 
 int kxtj9_update_odr (struct kxtj9_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kxtj9_enable(struct kxtj9_data *tj9)
{
	int err;

	err = kxtj9_device_power_on(tj9);
	if (err < 0)
		return err;

	/* ensure that PC1 is cleared before updating control registers */
	err = i2c_smbus_write_byte_data(tj9->client, CTRL_REG1, 0);
	if (err < 0)
		return err;

	/* only write INT_CTRL_REG1 if in irq mode */
	if (tj9->client->irq) {
		err = i2c_smbus_write_byte_data(tj9->client,
						INT_CTRL1, tj9->int_ctrl);
		if (err < 0)
			return err;
	}

	err = kxtj9_update_g_range(tj9, tj9->pdata.g_range);
	if (err < 0)
		return err;

	/* turn on outputs */
	tj9->ctrl_reg1 |= PC1_ON;
	err = i2c_smbus_write_byte_data(tj9->client, CTRL_REG1, tj9->ctrl_reg1);
	if (err < 0)
		return err;

	err = kxtj9_update_odr(tj9, tj9->last_poll_interval);
	if (err < 0)
		return err;

	/* clear initial interrupt if in irq mode */
	if (tj9->client->irq) {
		err = i2c_smbus_read_byte_data(tj9->client, INT_REL);
		if (err < 0) {
			dev_err(&tj9->client->dev,
				"error clearing interrupt: %d\n", err);
			goto fail;
		}
	}

	return 0;

fail:
	kxtj9_device_power_off(tj9);
	return err;
}