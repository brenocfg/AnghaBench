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
struct TYPE_2__ {int /*<<< orphan*/  pullup_pin; int /*<<< orphan*/  pullup_active_low; } ;
struct at91_udc {TYPE_1__ board; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at91rm9200_udc_pullup(struct at91_udc *udc, int is_on)
{
	int active = !udc->board.pullup_active_low;

	if (is_on)
		gpio_set_value(udc->board.pullup_pin, active);
	else
		gpio_set_value(udc->board.pullup_pin, !active);
}