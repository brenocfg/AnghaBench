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
struct ssp_data {int /*<<< orphan*/  mcu_reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ssp_toggle_mcu_reset_gpio(struct ssp_data *data)
{
	gpio_set_value(data->mcu_reset_gpio, 0);
	usleep_range(1000, 1200);
	gpio_set_value(data->mcu_reset_gpio, 1);
	msleep(50);
}