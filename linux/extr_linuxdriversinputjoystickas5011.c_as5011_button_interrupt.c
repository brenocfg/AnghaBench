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
struct as5011_device {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  button_gpio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_JOYSTICK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int gpio_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t as5011_button_interrupt(int irq, void *dev_id)
{
	struct as5011_device *as5011 = dev_id;
	int val = gpio_get_value_cansleep(as5011->button_gpio);

	input_report_key(as5011->input_dev, BTN_JOYSTICK, !val);
	input_sync(as5011->input_dev);

	return IRQ_HANDLED;
}