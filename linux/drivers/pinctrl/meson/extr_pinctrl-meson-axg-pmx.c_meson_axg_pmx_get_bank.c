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
struct meson_pmx_bank {unsigned int first; unsigned int last; } ;
struct meson_pinctrl {TYPE_1__* data; } ;
struct meson_axg_pmx_data {int num_pmx_banks; struct meson_pmx_bank* pmx_banks; } ;
struct TYPE_2__ {struct meson_axg_pmx_data* pmx_data; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int meson_axg_pmx_get_bank(struct meson_pinctrl *pc,
			unsigned int pin,
			struct meson_pmx_bank **bank)
{
	int i;
	struct meson_axg_pmx_data *pmx = pc->data->pmx_data;

	for (i = 0; i < pmx->num_pmx_banks; i++)
		if (pin >= pmx->pmx_banks[i].first &&
				pin <= pmx->pmx_banks[i].last) {
			*bank = &pmx->pmx_banks[i];
			return 0;
		}

	return -EINVAL;
}