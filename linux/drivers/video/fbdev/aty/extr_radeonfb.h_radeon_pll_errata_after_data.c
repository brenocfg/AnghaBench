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
struct radeonfb_info {int errata; } ;

/* Variables and functions */
 int CHIP_ERRATA_PLL_DELAY ; 
 int CHIP_ERRATA_R300_CG ; 
 int /*<<< orphan*/  radeon_pll_errata_after_data_slow (struct radeonfb_info*) ; 

__attribute__((used)) static inline void radeon_pll_errata_after_data(struct radeonfb_info *rinfo)
{
	if (rinfo->errata & (CHIP_ERRATA_PLL_DELAY|CHIP_ERRATA_R300_CG))
		radeon_pll_errata_after_data_slow(rinfo);
}