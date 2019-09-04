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
struct ektf2127_ts {int /*<<< orphan*/  power_gpios; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct ektf2127_ts* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int ektf2127_start(struct input_dev *dev)
{
	struct ektf2127_ts *ts = input_get_drvdata(dev);

	enable_irq(ts->client->irq);
	gpiod_set_value_cansleep(ts->power_gpios, 1);

	return 0;
}