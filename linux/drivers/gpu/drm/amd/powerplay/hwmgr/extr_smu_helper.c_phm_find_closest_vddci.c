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
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct pp_atomctrl_voltage_table {size_t count; TYPE_1__* entries; } ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 

uint16_t phm_find_closest_vddci(struct pp_atomctrl_voltage_table *vddci_table, uint16_t vddci)
{
	uint32_t  i;

	for (i = 0; i < vddci_table->count; i++) {
		if (vddci_table->entries[i].value >= vddci)
			return vddci_table->entries[i].value;
	}

	pr_debug("vddci is larger than max value in vddci_table\n");
	return vddci_table->entries[i-1].value;
}