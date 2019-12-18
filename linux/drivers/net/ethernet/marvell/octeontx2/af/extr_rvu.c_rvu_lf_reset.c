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
struct rvu_block {int /*<<< orphan*/  lfreset_reg; int /*<<< orphan*/  addr; int /*<<< orphan*/  implemented; } ;
struct rvu {int dummy; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int rvu_poll_reg (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int rvu_lf_reset(struct rvu *rvu, struct rvu_block *block, int lf)
{
	int err;

	if (!block->implemented)
		return 0;

	rvu_write64(rvu, block->addr, block->lfreset_reg, lf | BIT_ULL(12));
	err = rvu_poll_reg(rvu, block->addr, block->lfreset_reg, BIT_ULL(12),
			   true);
	return err;
}