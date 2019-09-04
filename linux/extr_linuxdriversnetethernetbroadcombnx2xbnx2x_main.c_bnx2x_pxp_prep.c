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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  PXP2_REG_RD_START_INIT ; 
 int /*<<< orphan*/  PXP2_REG_RQ_RBC_DONE ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 

__attribute__((used)) static void bnx2x_pxp_prep(struct bnx2x *bp)
{
	if (!CHIP_IS_E1(bp)) {
		REG_WR(bp, PXP2_REG_RD_START_INIT, 0);
		REG_WR(bp, PXP2_REG_RQ_RBC_DONE, 0);
		mmiowb();
	}
}