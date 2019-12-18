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
struct gpiomux {int /*<<< orphan*/  gpios; int /*<<< orphan*/  ngpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_TYPE (unsigned int) ; 
 int /*<<< orphan*/  DECLARE_BITMAP (unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 unsigned int* values ; 

__attribute__((used)) static void i2c_mux_gpio_set(const struct gpiomux *mux, unsigned val)
{
	DECLARE_BITMAP(values, BITS_PER_TYPE(val));

	values[0] = val;

	gpiod_set_array_value_cansleep(mux->ngpios, mux->gpios, NULL, values);
}