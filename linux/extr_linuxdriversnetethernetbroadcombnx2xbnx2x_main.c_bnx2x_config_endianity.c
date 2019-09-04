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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PXP2_REG_RD_CDURD_SWAP_MODE ; 
 int /*<<< orphan*/  PXP2_REG_RD_QM_SWAP_MODE ; 
 int /*<<< orphan*/  PXP2_REG_RD_SRC_SWAP_MODE ; 
 int /*<<< orphan*/  PXP2_REG_RD_TM_SWAP_MODE ; 
 int /*<<< orphan*/  PXP2_REG_RQ_CDU_ENDIAN_M ; 
 int /*<<< orphan*/  PXP2_REG_RQ_DBG_ENDIAN_M ; 
 int /*<<< orphan*/  PXP2_REG_RQ_HC_ENDIAN_M ; 
 int /*<<< orphan*/  PXP2_REG_RQ_QM_ENDIAN_M ; 
 int /*<<< orphan*/  PXP2_REG_RQ_SRC_ENDIAN_M ; 
 int /*<<< orphan*/  PXP2_REG_RQ_TM_ENDIAN_M ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_config_endianity(struct bnx2x *bp, u32 val)
{
	REG_WR(bp, PXP2_REG_RQ_QM_ENDIAN_M, val);
	REG_WR(bp, PXP2_REG_RQ_TM_ENDIAN_M, val);
	REG_WR(bp, PXP2_REG_RQ_SRC_ENDIAN_M, val);
	REG_WR(bp, PXP2_REG_RQ_CDU_ENDIAN_M, val);
	REG_WR(bp, PXP2_REG_RQ_DBG_ENDIAN_M, val);

	/* make sure this value is 0 */
	REG_WR(bp, PXP2_REG_RQ_HC_ENDIAN_M, 0);

	REG_WR(bp, PXP2_REG_RD_QM_SWAP_MODE, val);
	REG_WR(bp, PXP2_REG_RD_TM_SWAP_MODE, val);
	REG_WR(bp, PXP2_REG_RD_SRC_SWAP_MODE, val);
	REG_WR(bp, PXP2_REG_RD_CDURD_SWAP_MODE, val);
}