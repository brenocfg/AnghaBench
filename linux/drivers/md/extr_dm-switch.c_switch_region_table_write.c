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
struct switch_ctx {int* region_table; int region_table_entry_bits; } ;
typedef  int region_table_slot_t ;

/* Variables and functions */
 int /*<<< orphan*/  switch_get_position (struct switch_ctx*,unsigned long,unsigned long*,unsigned int*) ; 

__attribute__((used)) static void switch_region_table_write(struct switch_ctx *sctx, unsigned long region_nr,
				      unsigned value)
{
	unsigned long region_index;
	unsigned bit;
	region_table_slot_t pte;

	switch_get_position(sctx, region_nr, &region_index, &bit);

	pte = sctx->region_table[region_index];
	pte &= ~((((region_table_slot_t)1 << sctx->region_table_entry_bits) - 1) << bit);
	pte |= (region_table_slot_t)value << bit;
	sctx->region_table[region_index] = pte;
}