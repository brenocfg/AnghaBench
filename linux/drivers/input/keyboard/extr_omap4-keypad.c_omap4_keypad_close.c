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
struct omap4_keypad {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP4_KBD_IRQENABLE ; 
 int /*<<< orphan*/  OMAP4_KBD_IRQSTATUS ; 
 int /*<<< orphan*/  OMAP4_KBD_WAKEUPENABLE ; 
 int /*<<< orphan*/  OMAP4_VAL_IRQDISABLE ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct omap4_keypad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  kbd_read_irqreg (struct omap4_keypad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_write_irqreg (struct omap4_keypad*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_writel (struct omap4_keypad*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap4_keypad_close(struct input_dev *input)
{
	struct omap4_keypad *keypad_data = input_get_drvdata(input);

	disable_irq(keypad_data->irq);

	/* Disable interrupts and wake-up events */
	kbd_write_irqreg(keypad_data, OMAP4_KBD_IRQENABLE,
			 OMAP4_VAL_IRQDISABLE);
	kbd_writel(keypad_data, OMAP4_KBD_WAKEUPENABLE, 0);

	/* clear pending interrupts */
	kbd_write_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS,
			 kbd_read_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS));

	enable_irq(keypad_data->irq);

	pm_runtime_put_sync(input->dev.parent);
}