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
struct usb3503 {int /*<<< orphan*/  gpio_reset; int /*<<< orphan*/  gpio_connect; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int usb3503_reset(struct usb3503 *hub, int state)
{
	if (!state && gpio_is_valid(hub->gpio_connect))
		gpio_set_value_cansleep(hub->gpio_connect, 0);

	if (gpio_is_valid(hub->gpio_reset))
		gpio_set_value_cansleep(hub->gpio_reset, state);

	/* Wait T_HUBINIT == 4ms for hub logic to stabilize */
	if (state)
		usleep_range(4000, 10000);

	return 0;
}