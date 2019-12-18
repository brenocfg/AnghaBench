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
struct watchdog_device {int /*<<< orphan*/  status; } ;
struct gpio_wdt_priv {scalar_t__ state; int /*<<< orphan*/  gpiod; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int gpio_wdt_ping (struct watchdog_device*) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct gpio_wdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int gpio_wdt_start(struct watchdog_device *wdd)
{
	struct gpio_wdt_priv *priv = watchdog_get_drvdata(wdd);

	priv->state = 0;
	gpiod_direction_output(priv->gpiod, priv->state);

	set_bit(WDOG_HW_RUNNING, &wdd->status);

	return gpio_wdt_ping(wdd);
}