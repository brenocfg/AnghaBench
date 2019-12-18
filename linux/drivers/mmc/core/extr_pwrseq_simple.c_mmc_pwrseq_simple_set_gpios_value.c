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
struct gpio_descs {int ndescs; int /*<<< orphan*/  info; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct gpio_descs*) ; 
 unsigned long* bitmap_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_fill (unsigned long*,int) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int) ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 

__attribute__((used)) static void mmc_pwrseq_simple_set_gpios_value(struct mmc_pwrseq_simple *pwrseq,
					      int value)
{
	struct gpio_descs *reset_gpios = pwrseq->reset_gpios;

	if (!IS_ERR(reset_gpios)) {
		unsigned long *values;
		int nvalues = reset_gpios->ndescs;

		values = bitmap_alloc(nvalues, GFP_KERNEL);
		if (!values)
			return;

		if (value)
			bitmap_fill(values, nvalues);
		else
			bitmap_zero(values, nvalues);

		gpiod_set_array_value_cansleep(nvalues, reset_gpios->desc,
					       reset_gpios->info, values);

		kfree(values);
	}
}