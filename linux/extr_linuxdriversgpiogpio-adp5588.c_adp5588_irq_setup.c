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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct adp5588_gpio {struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int adp5588_irq_setup(struct adp5588_gpio *dev)
{
	struct i2c_client *client = dev->client;
	dev_warn(&client->dev, "interrupt support not compiled in\n");

	return 0;
}