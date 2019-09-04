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
struct ddc {int /*<<< orphan*/  pin_clock; int /*<<< orphan*/  pin_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  dal_ddc_close (struct ddc*) ; 
 int /*<<< orphan*/  dal_gpio_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ddc*) ; 

void dal_gpio_destroy_ddc(
	struct ddc **ddc)
{
	if (!ddc || !*ddc) {
		BREAK_TO_DEBUGGER();
		return;
	}

	dal_ddc_close(*ddc);
	dal_gpio_destroy(&(*ddc)->pin_data);
	dal_gpio_destroy(&(*ddc)->pin_clock);
	kfree(*ddc);

	*ddc = NULL;
}