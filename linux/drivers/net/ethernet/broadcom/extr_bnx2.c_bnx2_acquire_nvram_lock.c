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
 int /*<<< orphan*/  BNX2_NVM_SW_ARB ; 
 int BNX2_NVM_SW_ARB_ARB_ARB2 ; 
 int /*<<< orphan*/  BNX2_NVM_SW_ARB_ARB_REQ_SET2 ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int NVRAM_TIMEOUT_COUNT ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
bnx2_acquire_nvram_lock(struct bnx2 *bp)
{
	u32 val;
	int j;

	/* Request access to the flash interface. */
	BNX2_WR(bp, BNX2_NVM_SW_ARB, BNX2_NVM_SW_ARB_ARB_REQ_SET2);
	for (j = 0; j < NVRAM_TIMEOUT_COUNT; j++) {
		val = BNX2_RD(bp, BNX2_NVM_SW_ARB);
		if (val & BNX2_NVM_SW_ARB_ARB_ARB2)
			break;

		udelay(5);
	}

	if (j >= NVRAM_TIMEOUT_COUNT)
		return -EBUSY;

	return 0;
}