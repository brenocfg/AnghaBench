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
typedef  int u8 ;
struct orc_scb {int dummy; } ;
struct orc_host {int index; int** allocation_map; struct orc_scb* scb_virt; } ;

/* Variables and functions */

__attribute__((used)) static struct orc_scb *__orc_alloc_scb(struct orc_host * host)
{
	u8 channel;
	unsigned long idx;
	u8 index;
	u8 i;

	channel = host->index;
	for (i = 0; i < 8; i++) {
		for (index = 0; index < 32; index++) {
			if ((host->allocation_map[channel][i] >> index) & 0x01) {
				host->allocation_map[channel][i] &= ~(1 << index);
				idx = index + 32 * i;
				/*
				 * Translate the index to a structure instance
				 */
				return host->scb_virt + idx;
			}
		}
	}
	return NULL;
}