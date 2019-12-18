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
struct gpio_vibrator {int running; int /*<<< orphan*/  play_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_vibrator_stop (struct gpio_vibrator*) ; 
 struct gpio_vibrator* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void gpio_vibrator_close(struct input_dev *input)
{
	struct gpio_vibrator *vibrator = input_get_drvdata(input);

	cancel_work_sync(&vibrator->play_work);
	gpio_vibrator_stop(vibrator);
	vibrator->running = false;
}