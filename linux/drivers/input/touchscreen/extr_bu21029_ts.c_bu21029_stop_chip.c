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
struct bu21029_ts_data {int /*<<< orphan*/  vdd; int /*<<< orphan*/  timer; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  bu21029_put_chip_in_reset (struct bu21029_ts_data*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct bu21029_ts_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bu21029_stop_chip(struct input_dev *dev)
{
	struct bu21029_ts_data *bu21029 = input_get_drvdata(dev);

	disable_irq(bu21029->client->irq);
	del_timer_sync(&bu21029->timer);

	bu21029_put_chip_in_reset(bu21029);
	regulator_disable(bu21029->vdd);
}