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
typedef  int u64 ;
struct rvu_block {int /*<<< orphan*/  lookup_reg; int /*<<< orphan*/  addr; } ;
struct rvu {int dummy; } ;

/* Variables and functions */
 unsigned long long rvu_read64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rvu_lookup_rsrc(struct rvu *rvu, struct rvu_block *block,
			   int pcifunc, int slot)
{
	u64 val;

	val = ((u64)pcifunc << 24) | (slot << 16) | (1ULL << 13);
	rvu_write64(rvu, block->addr, block->lookup_reg, val);
	/* Wait for the lookup to finish */
	/* TODO: put some timeout here */
	while (rvu_read64(rvu, block->addr, block->lookup_reg) & (1ULL << 13))
		;

	val = rvu_read64(rvu, block->addr, block->lookup_reg);

	/* Check LF valid bit */
	if (!(val & (1ULL << 12)))
		return -1;

	return (val & 0xFFF);
}