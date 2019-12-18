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
struct ddc {int /*<<< orphan*/  pin_data; } ;
typedef  enum gpio_ddc_line { ____Placeholder_gpio_ddc_line } gpio_ddc_line ;

/* Variables and functions */
 int /*<<< orphan*/  dal_gpio_get_enum (int /*<<< orphan*/ ) ; 

enum gpio_ddc_line dal_ddc_get_line(
	const struct ddc *ddc)
{
	return (enum gpio_ddc_line)dal_gpio_get_enum(ddc->pin_data);
}