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
struct mms114_data {int /*<<< orphan*/  core_reg; int /*<<< orphan*/  io_reg; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMS114_POWERON_DELAY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int mms114_setup_regs (struct mms114_data*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mms114_start(struct mms114_data *data)
{
	struct i2c_client *client = data->client;
	int error;

	error = regulator_enable(data->core_reg);
	if (error) {
		dev_err(&client->dev, "Failed to enable avdd: %d\n", error);
		return error;
	}

	error = regulator_enable(data->io_reg);
	if (error) {
		dev_err(&client->dev, "Failed to enable vdd: %d\n", error);
		regulator_disable(data->core_reg);
		return error;
	}

	msleep(MMS114_POWERON_DELAY);

	error = mms114_setup_regs(data);
	if (error < 0) {
		regulator_disable(data->io_reg);
		regulator_disable(data->core_reg);
		return error;
	}

	enable_irq(client->irq);

	return 0;
}