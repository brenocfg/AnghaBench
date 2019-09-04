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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ BNX2X_PREV_UNDI_BD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2X_PREV_UNDI_PROD (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_PREV_UNDI_PROD_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2X_PREV_UNDI_PROD_ADDR_H (int) ; 
 scalar_t__ BNX2X_PREV_UNDI_RCQ (int /*<<< orphan*/ ) ; 
 int BP_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_prev_unload_undi_inc(struct bnx2x *bp, u8 inc)
{
	u16 rcq, bd;
	u32 addr, tmp_reg;

	if (BP_FUNC(bp) < 2)
		addr = BNX2X_PREV_UNDI_PROD_ADDR(BP_PORT(bp));
	else
		addr = BNX2X_PREV_UNDI_PROD_ADDR_H(BP_FUNC(bp) - 2);

	tmp_reg = REG_RD(bp, addr);
	rcq = BNX2X_PREV_UNDI_RCQ(tmp_reg) + inc;
	bd = BNX2X_PREV_UNDI_BD(tmp_reg) + inc;

	tmp_reg = BNX2X_PREV_UNDI_PROD(rcq, bd);
	REG_WR(bp, addr, tmp_reg);

	BNX2X_DEV_INFO("UNDI producer [%d/%d][%08x] rings bd -> 0x%04x, rcq -> 0x%04x\n",
		       BP_PORT(bp), BP_FUNC(bp), addr, bd, rcq);
}