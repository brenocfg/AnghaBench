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
struct wacom_i2c {struct i2c_client* client; } ;
struct input_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct wacom_i2c* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int wacom_i2c_open(struct input_dev *dev)
{
	struct wacom_i2c *wac_i2c = input_get_drvdata(dev);
	struct i2c_client *client = wac_i2c->client;

	enable_irq(client->irq);

	return 0;
}