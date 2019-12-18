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
struct ps2_gpio_data {int /*<<< orphan*/  irq; int /*<<< orphan*/  tx_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ps2_gpio_close(struct serio *serio)
{
	struct ps2_gpio_data *drvdata = serio->port_data;

	flush_delayed_work(&drvdata->tx_work);
	disable_irq(drvdata->irq);
}