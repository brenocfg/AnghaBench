#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ngpio; int base; } ;
struct TYPE_6__ {TYPE_2__ gpio_chip; TYPE_1__** active_gpios; } ;
struct TYPE_4__ {int /*<<< orphan*/  vg_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_3__ viafb_gpio_config ; 

int viafb_gpio_lookup(const char *name)
{
	int i;

	for (i = 0; i < viafb_gpio_config.gpio_chip.ngpio; i++)
		if (!strcmp(name, viafb_gpio_config.active_gpios[i]->vg_name))
			return viafb_gpio_config.gpio_chip.base + i;
	return -1;
}