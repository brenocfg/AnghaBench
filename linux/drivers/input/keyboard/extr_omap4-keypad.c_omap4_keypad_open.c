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
 int OMAP4_DEF_CTRL_NOSOFTMODE ; 
 int OMAP4_DEF_CTRL_PTV_SHIFT ; 
 int OMAP4_DEF_IRQENABLE_EVENTEN ; 
 int OMAP4_DEF_IRQENABLE_LONGKEY ; 
 int OMAP4_DEF_WUP_EVENT_ENA ; 
 int OMAP4_DEF_WUP_LONG_KEY_ENA ; 
 int /*<<< orphan*/  OMAP4_KBD_CTRL ; 
 int /*<<< orphan*/  OMAP4_KBD_DEBOUNCINGTIME ; 
 int /*<<< orphan*/  OMAP4_KBD_IRQENABLE ; 
 int /*<<< orphan*/  OMAP4_KBD_IRQSTATUS ; 
 int /*<<< orphan*/  OMAP4_KBD_WAKEUPENABLE ; 
 int OMAP4_KEYPAD_PTV_DIV_128 ; 
 int OMAP4_VAL_DEBOUNCINGTIME_16MS ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct omap4_keypad* input_get_drvdata (struct input_dev*) ; 
 int kbd_read_irqreg (struct omap4_keypad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_write_irqreg (struct omap4_keypad*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kbd_writel (struct omap4_keypad*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap4_keypad_open(struct input_dev *input)
{
	struct omap4_keypad *keypad_data = input_get_drvdata(input);

	pm_runtime_get_sync(input->dev.parent);

	disable_irq(keypad_data->irq);

	kbd_writel(keypad_data, OMAP4_KBD_CTRL,
			OMAP4_DEF_CTRL_NOSOFTMODE |
			(OMAP4_KEYPAD_PTV_DIV_128 << OMAP4_DEF_CTRL_PTV_SHIFT));
	kbd_writel(keypad_data, OMAP4_KBD_DEBOUNCINGTIME,
			OMAP4_VAL_DEBOUNCINGTIME_16MS);
	/* clear pending interrupts */
	kbd_write_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS,
			 kbd_read_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS));
	kbd_write_irqreg(keypad_data, OMAP4_KBD_IRQENABLE,
			OMAP4_DEF_IRQENABLE_EVENTEN |
				OMAP4_DEF_IRQENABLE_LONGKEY);
	kbd_writel(keypad_data, OMAP4_KBD_WAKEUPENABLE,
			OMAP4_DEF_WUP_EVENT_ENA | OMAP4_DEF_WUP_LONG_KEY_ENA);

	enable_irq(keypad_data->irq);

	return 0;
}