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
struct switch_ctx {int region_size_bits; unsigned int nr_paths; int /*<<< orphan*/  region_size; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  sector_div (int,int /*<<< orphan*/ ) ; 
 unsigned int switch_region_table_read (struct switch_ctx*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned switch_get_path_nr(struct switch_ctx *sctx, sector_t offset)
{
	unsigned path_nr;
	sector_t p;

	p = offset;
	if (sctx->region_size_bits >= 0)
		p >>= sctx->region_size_bits;
	else
		sector_div(p, sctx->region_size);

	path_nr = switch_region_table_read(sctx, p);

	/* This can only happen if the processor uses non-atomic stores. */
	if (unlikely(path_nr >= sctx->nr_paths))
		path_nr = 0;

	return path_nr;
}