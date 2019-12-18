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
struct ddc {int /*<<< orphan*/  pin_data; int /*<<< orphan*/  pin_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_gpio_close (int /*<<< orphan*/ ) ; 

void dal_ddc_close(
	struct ddc *ddc)
{
	dal_gpio_close(ddc->pin_clock);
	dal_gpio_close(ddc->pin_data);
}