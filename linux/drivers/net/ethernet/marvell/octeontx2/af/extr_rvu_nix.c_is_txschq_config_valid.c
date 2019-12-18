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
typedef  int u16 ;
struct rvu {int dummy; } ;

/* Variables and functions */
 int NIX_AF_MDQX_PARENT (int /*<<< orphan*/ ) ; 
 int NIX_AF_TL2X_PARENT (int /*<<< orphan*/ ) ; 
 int NIX_AF_TL3X_PARENT (int /*<<< orphan*/ ) ; 
 int NIX_AF_TL4X_PARENT (int /*<<< orphan*/ ) ; 
 int NIX_TXSCH_LVL_TL1 ; 
 int NIX_TXSCH_LVL_TL2 ; 
 int NIX_TXSCH_LVL_TL3 ; 
 int NIX_TXSCH_LVL_TL4 ; 
 int /*<<< orphan*/  TXSCHQ_HWREGMAP ; 
 int TXSCHQ_IDX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXSCHQ_IDX_SHIFT ; 
 int /*<<< orphan*/  is_valid_txschq (struct rvu*,int,int,int,int) ; 
 int /*<<< orphan*/  rvu_check_valid_reg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool is_txschq_config_valid(struct rvu *rvu, u16 pcifunc, int blkaddr,
				   int lvl, u64 reg, u64 regval)
{
	u64 regbase = reg & 0xFFFF;
	u16 schq, parent;

	if (!rvu_check_valid_reg(TXSCHQ_HWREGMAP, lvl, reg))
		return false;

	schq = TXSCHQ_IDX(reg, TXSCHQ_IDX_SHIFT);
	/* Check if this schq belongs to this PF/VF or not */
	if (!is_valid_txschq(rvu, blkaddr, lvl, pcifunc, schq))
		return false;

	parent = (regval >> 16) & 0x1FF;
	/* Validate MDQ's TL4 parent */
	if (regbase == NIX_AF_MDQX_PARENT(0) &&
	    !is_valid_txschq(rvu, blkaddr, NIX_TXSCH_LVL_TL4, pcifunc, parent))
		return false;

	/* Validate TL4's TL3 parent */
	if (regbase == NIX_AF_TL4X_PARENT(0) &&
	    !is_valid_txschq(rvu, blkaddr, NIX_TXSCH_LVL_TL3, pcifunc, parent))
		return false;

	/* Validate TL3's TL2 parent */
	if (regbase == NIX_AF_TL3X_PARENT(0) &&
	    !is_valid_txschq(rvu, blkaddr, NIX_TXSCH_LVL_TL2, pcifunc, parent))
		return false;

	/* Validate TL2's TL1 parent */
	if (regbase == NIX_AF_TL2X_PARENT(0) &&
	    !is_valid_txschq(rvu, blkaddr, NIX_TXSCH_LVL_TL1, pcifunc, parent))
		return false;

	return true;
}