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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  REG_FBPR_AR ; 
 int /*<<< orphan*/  REG_FBPR_BAR ; 
 int /*<<< orphan*/  REG_FBPR_BARE ; 
 int __bman_requires_cleanup ; 
 int bm_ccsr_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_ccsr_out (int /*<<< orphan*/ ,int) ; 
 int ilog2 (int) ; 
 scalar_t__ is_power_of_2 (int) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int bm_set_memory(u64 ba, u32 size)
{
	u32 bar, bare;
	u32 exp = ilog2(size);
	/* choke if size isn't within range */
	DPAA_ASSERT(size >= 4096 && size <= 1024*1024*1024 &&
		   is_power_of_2(size));
	/* choke if '[e]ba' has lower-alignment than 'size' */
	DPAA_ASSERT(!(ba & (size - 1)));

	/* Check to see if BMan has already been initialized */
	bar = bm_ccsr_in(REG_FBPR_BAR);
	if (bar) {
		/* Maker sure ba == what was programmed) */
		bare = bm_ccsr_in(REG_FBPR_BARE);
		if (bare != upper_32_bits(ba) || bar != lower_32_bits(ba)) {
			pr_err("Attempted to reinitialize BMan with different BAR, got 0x%llx read BARE=0x%x BAR=0x%x\n",
			       ba, bare, bar);
			return -ENOMEM;
		}
		pr_info("BMan BAR already configured\n");
		__bman_requires_cleanup = 1;
		return 1;
	}

	bm_ccsr_out(REG_FBPR_BARE, upper_32_bits(ba));
	bm_ccsr_out(REG_FBPR_BAR, lower_32_bits(ba));
	bm_ccsr_out(REG_FBPR_AR, exp - 1);
	return 0;
}