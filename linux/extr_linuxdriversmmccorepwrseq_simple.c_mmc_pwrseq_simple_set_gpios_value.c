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
struct mmc_pwrseq_simple {struct gpio_descs* reset_gpios; } ;
struct gpio_descs {int ndescs; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct gpio_descs*) ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_pwrseq_simple_set_gpios_value(struct mmc_pwrseq_simple *pwrseq,
					      int value)
{
	struct gpio_descs *reset_gpios = pwrseq->reset_gpios;

	if (!IS_ERR(reset_gpios)) {
		int i, *values;
		int nvalues = reset_gpios->ndescs;

		values = kmalloc_array(nvalues, sizeof(int), GFP_KERNEL);
		if (!values)
			return;

		for (i = 0; i < nvalues; i++)
			values[i] = value;

		gpiod_set_array_value_cansleep(nvalues, reset_gpios->desc, values);
		kfree(values);
	}
}