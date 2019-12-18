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
typedef  int /*<<< orphan*/  u64 ;
struct rvu_block {int /*<<< orphan*/  implemented; } ;
struct rvu {TYPE_1__* hw; } ;
struct TYPE_2__ {struct rvu_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int) ; 
 int /*<<< orphan*/  rvu_poll_reg (struct rvu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvu_block_reset(struct rvu *rvu, int blkaddr, u64 rst_reg)
{
	struct rvu_block *block = &rvu->hw->block[blkaddr];

	if (!block->implemented)
		return;

	rvu_write64(rvu, blkaddr, rst_reg, BIT_ULL(0));
	rvu_poll_reg(rvu, blkaddr, rst_reg, BIT_ULL(63), true);
}