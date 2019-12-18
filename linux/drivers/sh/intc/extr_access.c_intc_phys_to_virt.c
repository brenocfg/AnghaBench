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
struct intc_window {unsigned long phys; unsigned long size; scalar_t__ virt; } ;
struct intc_desc_int {int nr_windows; struct intc_window* window; } ;

/* Variables and functions */

unsigned long intc_phys_to_virt(struct intc_desc_int *d, unsigned long address)
{
	struct intc_window *window;
	int k;

	/* scan through physical windows and convert address */
	for (k = 0; k < d->nr_windows; k++) {
		window = d->window + k;

		if (address < window->phys)
			continue;

		if (address >= (window->phys + window->size))
			continue;

		address -= window->phys;
		address += (unsigned long)window->virt;

		return address;
	}

	/* no windows defined, register must be 1:1 mapped virt:phys */
	return address;
}