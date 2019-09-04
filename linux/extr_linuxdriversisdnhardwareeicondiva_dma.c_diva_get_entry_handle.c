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
struct _diva_dma_map_entry {void* addr_handle; } ;

/* Variables and functions */

void *diva_get_entry_handle(struct _diva_dma_map_entry *pmap, int nr) {
	return (pmap[nr].addr_handle);
}