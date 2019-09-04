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
struct tosa_bt_data {int /*<<< orphan*/  gpio_reset; int /*<<< orphan*/  gpio_pwr; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void tosa_bt_on(struct tosa_bt_data *data)
{
	gpio_set_value(data->gpio_reset, 0);
	gpio_set_value(data->gpio_pwr, 1);
	gpio_set_value(data->gpio_reset, 1);
	mdelay(20);
	gpio_set_value(data->gpio_reset, 0);
}