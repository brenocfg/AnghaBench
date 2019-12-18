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
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mms114_stop(struct mms114_data *data)
{
	struct i2c_client *client = data->client;
	int error;

	disable_irq(client->irq);

	error = regulator_disable(data->io_reg);
	if (error)
		dev_warn(&client->dev, "Failed to disable vdd: %d\n", error);

	error = regulator_disable(data->core_reg);
	if (error)
		dev_warn(&client->dev, "Failed to disable avdd: %d\n", error);
}