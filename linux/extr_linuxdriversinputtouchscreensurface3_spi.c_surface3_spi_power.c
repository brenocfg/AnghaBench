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
struct surface3_ts_data {int /*<<< orphan*/ * gpiod_rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void surface3_spi_power(struct surface3_ts_data *data, bool on)
{
	gpiod_set_value(data->gpiod_rst[0], on);
	gpiod_set_value(data->gpiod_rst[1], on);
	/* let the device settle a little */
	msleep(20);
}