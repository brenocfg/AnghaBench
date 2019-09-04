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
typedef  scalar_t__ u64 ;
typedef  int const u32 ;
struct TYPE_2__ {scalar_t__ base; } ;
struct nfit_blk_mmio {unsigned int size; TYPE_1__ addr; scalar_t__ num_lines; } ;
struct nfit_blk {scalar_t__ stat_offset; struct nfit_blk_mmio* mmio; } ;

/* Variables and functions */
 size_t DCR ; 
 int const readl (scalar_t__) ; 
 scalar_t__ to_interleave_offset (scalar_t__,struct nfit_blk_mmio*) ; 

__attribute__((used)) static u32 read_blk_stat(struct nfit_blk *nfit_blk, unsigned int bw)
{
	struct nfit_blk_mmio *mmio = &nfit_blk->mmio[DCR];
	u64 offset = nfit_blk->stat_offset + mmio->size * bw;
	const u32 STATUS_MASK = 0x80000037;

	if (mmio->num_lines)
		offset = to_interleave_offset(offset, mmio);

	return readl(mmio->addr.base + offset) & STATUS_MASK;
}