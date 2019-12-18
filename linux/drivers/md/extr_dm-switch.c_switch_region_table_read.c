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
struct switch_ctx {int region_table_entry_bits; int /*<<< orphan*/ * region_table; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_get_position (struct switch_ctx*,unsigned long,unsigned long*,unsigned int*) ; 

__attribute__((used)) static unsigned switch_region_table_read(struct switch_ctx *sctx, unsigned long region_nr)
{
	unsigned long region_index;
	unsigned bit;

	switch_get_position(sctx, region_nr, &region_index, &bit);

	return (READ_ONCE(sctx->region_table[region_index]) >> bit) &
		((1 << sctx->region_table_entry_bits) - 1);
}