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
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct icn8318_data* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int icn8318_start(struct input_dev *dev)
{
	struct icn8318_data *data = input_get_drvdata(dev);

	enable_irq(data->client->irq);
	gpiod_set_value_cansleep(data->wake_gpio, 1);

	return 0;
}