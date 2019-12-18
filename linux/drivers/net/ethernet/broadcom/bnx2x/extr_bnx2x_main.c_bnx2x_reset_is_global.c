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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_GLOBAL_RESET_BIT ; 
 int /*<<< orphan*/  BNX2X_RECOVERY_GLOB_REG ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bnx2x_reset_is_global(struct bnx2x *bp)
{
	u32 val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);

	DP(NETIF_MSG_HW, "GEN_REG_VAL=0x%08x\n", val);
	return (val & BNX2X_GLOBAL_RESET_BIT) ? true : false;
}