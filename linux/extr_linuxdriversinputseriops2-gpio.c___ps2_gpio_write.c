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
struct serio {struct ps2_gpio_data* port_data; } ;
struct ps2_gpio_data {unsigned char tx_byte; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  mode; int /*<<< orphan*/  gpio_clk; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS2_MODE_TX ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

__attribute__((used)) static int __ps2_gpio_write(struct serio *serio, unsigned char val)
{
	struct ps2_gpio_data *drvdata = serio->port_data;

	disable_irq_nosync(drvdata->irq);
	gpiod_direction_output(drvdata->gpio_clk, 0);

	drvdata->mode = PS2_MODE_TX;
	drvdata->tx_byte = val;

	schedule_delayed_work(&drvdata->tx_work, usecs_to_jiffies(200));

	return 0;
}