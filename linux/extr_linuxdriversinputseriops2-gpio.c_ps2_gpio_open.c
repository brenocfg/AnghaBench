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
struct ps2_gpio_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps2_gpio_open(struct serio *serio)
{
	struct ps2_gpio_data *drvdata = serio->port_data;

	enable_irq(drvdata->irq);
	return 0;
}