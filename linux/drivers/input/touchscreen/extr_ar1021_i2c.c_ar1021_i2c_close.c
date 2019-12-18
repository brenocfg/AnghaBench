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
struct input_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct ar1021_i2c {struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct ar1021_i2c* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void ar1021_i2c_close(struct input_dev *dev)
{
	struct ar1021_i2c *ar1021 = input_get_drvdata(dev);
	struct i2c_client *client = ar1021->client;

	disable_irq(client->irq);
}