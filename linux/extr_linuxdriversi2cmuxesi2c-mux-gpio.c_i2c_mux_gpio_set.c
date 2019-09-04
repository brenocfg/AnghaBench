#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int n_gpios; } ;
struct gpiomux {unsigned int* values; int /*<<< orphan*/  gpios; TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (int,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void i2c_mux_gpio_set(const struct gpiomux *mux, unsigned val)
{
	int i;

	for (i = 0; i < mux->data.n_gpios; i++)
		mux->values[i] = (val >> i) & 1;

	gpiod_set_array_value_cansleep(mux->data.n_gpios,
				       mux->gpios, mux->values);
}