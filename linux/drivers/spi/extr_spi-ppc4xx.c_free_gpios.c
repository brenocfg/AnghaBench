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
struct ppc4xx_spi {int /*<<< orphan*/ * gpios; TYPE_1__* master; } ;
struct TYPE_2__ {int num_chipselect; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_gpios(struct ppc4xx_spi *hw)
{
	if (hw->master->num_chipselect) {
		int i;
		for (i = 0; i < hw->master->num_chipselect; i++)
			if (gpio_is_valid(hw->gpios[i]))
				gpio_free(hw->gpios[i]);

		kfree(hw->gpios);
		hw->gpios = NULL;
	}
}