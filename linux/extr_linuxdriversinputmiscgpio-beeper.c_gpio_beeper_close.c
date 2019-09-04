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
struct input_dev {int dummy; } ;
struct gpio_beeper {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_beeper_toggle (struct gpio_beeper*,int) ; 
 struct gpio_beeper* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void gpio_beeper_close(struct input_dev *input)
{
	struct gpio_beeper *beep = input_get_drvdata(input);

	cancel_work_sync(&beep->work);
	gpio_beeper_toggle(beep, false);
}