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
struct radeonfb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_CNTL_DATA ; 
 int /*<<< orphan*/  CLOCK_CNTL_INDEX ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTREG8 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  radeon_pll_errata_after_data (struct radeonfb_info*) ; 
 int /*<<< orphan*/  radeon_pll_errata_after_index (struct radeonfb_info*) ; 

void __OUTPLL(struct radeonfb_info *rinfo, unsigned int index, u32 val)
{
	OUTREG8(CLOCK_CNTL_INDEX, (index & 0x0000003f) | 0x00000080);
	radeon_pll_errata_after_index(rinfo);
	OUTREG(CLOCK_CNTL_DATA, val);
	radeon_pll_errata_after_data(rinfo);
}