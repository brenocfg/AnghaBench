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
struct radeonfb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_CNTL_DATA ; 
 int /*<<< orphan*/  CLOCK_CNTL_INDEX ; 
 int INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_pll_errata_after_data (struct radeonfb_info*) ; 
 int /*<<< orphan*/  radeon_pll_errata_after_index (struct radeonfb_info*) ; 

u32 __INPLL(struct radeonfb_info *rinfo, u32 addr)
{
	u32 data;

	OUTREG8(CLOCK_CNTL_INDEX, addr & 0x0000003f);
	radeon_pll_errata_after_index(rinfo);
	data = INREG(CLOCK_CNTL_DATA);
	radeon_pll_errata_after_data(rinfo);
	return data;
}