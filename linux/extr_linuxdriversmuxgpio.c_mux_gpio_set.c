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
struct mux_gpio {int* val; TYPE_1__* gpios; } ;
struct mux_control {int /*<<< orphan*/  chip; } ;
struct TYPE_2__ {int ndescs; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (int,int /*<<< orphan*/ ,int*) ; 
 struct mux_gpio* mux_chip_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mux_gpio_set(struct mux_control *mux, int state)
{
	struct mux_gpio *mux_gpio = mux_chip_priv(mux->chip);
	int i;

	for (i = 0; i < mux_gpio->gpios->ndescs; i++)
		mux_gpio->val[i] = (state >> i) & 1;

	gpiod_set_array_value_cansleep(mux_gpio->gpios->ndescs,
				       mux_gpio->gpios->desc,
				       mux_gpio->val);

	return 0;
}