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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_DBG_REG_BCR ; 
 int /*<<< orphan*/  AARCH64_DBG_REG_BVR ; 
 int /*<<< orphan*/  AARCH64_DBG_REG_NAME_BCR ; 
 int /*<<< orphan*/  AARCH64_DBG_REG_NAME_BVR ; 
 int /*<<< orphan*/  AARCH64_DBG_REG_NAME_WCR ; 
 int /*<<< orphan*/  AARCH64_DBG_REG_NAME_WVR ; 
 int /*<<< orphan*/  AARCH64_DBG_REG_WCR ; 
 int /*<<< orphan*/  AARCH64_DBG_REG_WVR ; 
 int /*<<< orphan*/  GEN_READ_WB_REG_CASES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 

__attribute__((used)) static u64 read_wb_reg(int reg, int n)
{
	u64 val = 0;

	switch (reg + n) {
	GEN_READ_WB_REG_CASES(AARCH64_DBG_REG_BVR, AARCH64_DBG_REG_NAME_BVR, val);
	GEN_READ_WB_REG_CASES(AARCH64_DBG_REG_BCR, AARCH64_DBG_REG_NAME_BCR, val);
	GEN_READ_WB_REG_CASES(AARCH64_DBG_REG_WVR, AARCH64_DBG_REG_NAME_WVR, val);
	GEN_READ_WB_REG_CASES(AARCH64_DBG_REG_WCR, AARCH64_DBG_REG_NAME_WCR, val);
	default:
		pr_warning("attempt to read from unknown breakpoint register %d\n", n);
	}

	return val;
}