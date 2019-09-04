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
struct hdc100x_data {int config; } ;

/* Variables and functions */
 int HDC100X_REG_CONFIG_HEATER_EN ; 

__attribute__((used)) static int hdc100x_get_heater_status(struct hdc100x_data *data)
{
	return !!(data->config & HDC100X_REG_CONFIG_HEATER_EN);
}