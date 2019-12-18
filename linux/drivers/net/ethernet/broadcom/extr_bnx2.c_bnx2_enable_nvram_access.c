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
 int /*<<< orphan*/  BNX2_NVM_ACCESS_ENABLE ; 
 int BNX2_NVM_ACCESS_ENABLE_EN ; 
 int BNX2_NVM_ACCESS_ENABLE_WR_EN ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bnx2_enable_nvram_access(struct bnx2 *bp)
{
	u32 val;

	val = BNX2_RD(bp, BNX2_NVM_ACCESS_ENABLE);
	/* Enable both bits, even on read. */
	BNX2_WR(bp, BNX2_NVM_ACCESS_ENABLE,
		val | BNX2_NVM_ACCESS_ENABLE_EN | BNX2_NVM_ACCESS_ENABLE_WR_EN);
}