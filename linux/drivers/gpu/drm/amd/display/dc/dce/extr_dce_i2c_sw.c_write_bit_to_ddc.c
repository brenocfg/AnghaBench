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
typedef  int uint32_t ;
struct ddc {int /*<<< orphan*/  pin_clock; int /*<<< orphan*/  pin_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void write_bit_to_ddc(
	struct ddc *ddc,
	bool data_nor_clock,
	bool bit)
{
	uint32_t value = bit ? 1 : 0;

	if (data_nor_clock)
		dal_gpio_set_value(ddc->pin_data, value);
	else
		dal_gpio_set_value(ddc->pin_clock, value);
}