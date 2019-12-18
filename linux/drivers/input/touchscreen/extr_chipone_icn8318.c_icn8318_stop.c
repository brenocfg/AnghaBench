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
struct input_dev {int dummy; } ;
struct icn8318_data {int /*<<< orphan*/  wake_gpio; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICN8318_POWER_HIBERNATE ; 
 int /*<<< orphan*/  ICN8318_REG_POWER ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct icn8318_data* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void icn8318_stop(struct input_dev *dev)
{
	struct icn8318_data *data = input_get_drvdata(dev);

	disable_irq(data->client->irq);
	i2c_smbus_write_byte_data(data->client, ICN8318_REG_POWER,
				  ICN8318_POWER_HIBERNATE);
	gpiod_set_value_cansleep(data->wake_gpio, 0);
}