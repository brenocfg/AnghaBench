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
struct _diva_dma_map_entry {int busy; scalar_t__ local_ram_addr; } ;

/* Variables and functions */

int diva_alloc_dma_map_entry(struct _diva_dma_map_entry *pmap) {
	int i;
	for (i = 0; (pmap && pmap[i].local_ram_addr); i++) {
		if (!pmap[i].busy) {
			pmap[i].busy = 1;
			return (i);
		}
	}
	return (-1);
}