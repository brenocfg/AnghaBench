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
typedef  int u32 ;
struct bnx2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_MISC_CFG ; 
 int BNX2_MISC_CFG_NVM_WR_EN ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bnx2_disable_nvram_write(struct bnx2 *bp)
{
	u32 val;

	val = BNX2_RD(bp, BNX2_MISC_CFG);
	BNX2_WR(bp, BNX2_MISC_CFG, val & ~BNX2_MISC_CFG_NVM_WR_EN);
}