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
struct gpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  dal_gpio_close (struct gpio*) ; 
 int /*<<< orphan*/  dal_gpio_destroy (struct gpio**) ; 
 int /*<<< orphan*/  kfree (struct gpio*) ; 

void dal_gpio_destroy_generic_mux(
	struct gpio **mux)
{
	if (!mux || !*mux) {
		ASSERT_CRITICAL(false);
		return;
	}

	dal_gpio_close(*mux);
	dal_gpio_destroy(mux);
	kfree(*mux);

	*mux = NULL;
}