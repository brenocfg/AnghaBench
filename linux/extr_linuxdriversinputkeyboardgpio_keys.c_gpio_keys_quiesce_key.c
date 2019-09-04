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
struct gpio_button_data {int /*<<< orphan*/  release_timer; int /*<<< orphan*/  work; scalar_t__ gpiod; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gpio_keys_quiesce_key(void *data)
{
	struct gpio_button_data *bdata = data;

	if (bdata->gpiod)
		cancel_delayed_work_sync(&bdata->work);
	else
		del_timer_sync(&bdata->release_timer);
}