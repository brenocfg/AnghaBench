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
struct timer_list {int dummy; } ;
struct at91_udc {int /*<<< orphan*/  vbus_timer_work; } ;

/* Variables and functions */
 struct at91_udc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct at91_udc* udc ; 
 int /*<<< orphan*/  vbus_timer ; 

__attribute__((used)) static void at91_vbus_timer(struct timer_list *t)
{
	struct at91_udc *udc = from_timer(udc, t, vbus_timer);

	/*
	 * If we are polling vbus it is likely that the gpio is on an
	 * bus such as i2c or spi which may sleep, so schedule some work
	 * to read the vbus gpio
	 */
	schedule_work(&udc->vbus_timer_work);
}