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
struct isp1704_charger {int /*<<< orphan*/  enable_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isp1704_charger_set_power(struct isp1704_charger *isp, bool on)
{
	gpiod_set_value(isp->enable_gpio, on);
}