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
typedef  int uint32_t ;
struct dc_link {int /*<<< orphan*/  hpd_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_gpio_get_value (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dal_gpio_lock_pin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dal_gpio_unlock_pin (int /*<<< orphan*/ ) ; 

bool dc_link_get_hpd_state(struct dc_link *dc_link)
{
	uint32_t state;

	dal_gpio_lock_pin(dc_link->hpd_gpio);
	dal_gpio_get_value(dc_link->hpd_gpio, &state);
	dal_gpio_unlock_pin(dc_link->hpd_gpio);

	return state;
}