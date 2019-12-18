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
typedef  int u8 ;
struct atyfb_par {scalar_t__ clk_wr_offset; } ;

/* Variables and functions */
 scalar_t__ CLOCK_CNTL ; 
 int CLOCK_STROBE ; 
 int aty_ld_8 (scalar_t__,struct atyfb_par const*) ; 
 int /*<<< orphan*/  aty_st_8 (scalar_t__,int,struct atyfb_par const*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void aty_StrobeClock(const struct atyfb_par *par)
{
	u8 tmp;

	udelay(26);

	tmp = aty_ld_8(CLOCK_CNTL, par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset, tmp | CLOCK_STROBE, par);
	return;
}