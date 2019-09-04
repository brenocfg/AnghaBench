#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  unsigned long u64 ;
typedef  int u32 ;
struct TYPE_2__ {int pllsw; scalar_t__ offset; scalar_t__ clk38div; int /*<<< orphan*/  branch; } ;

/* Variables and functions */
 size_t PRCMU_SGACLK ; 
 int PRCM_CLK_MGT_CLK38 ; 
 int PRCM_CLK_MGT_CLK38DIV ; 
 int PRCM_CLK_MGT_CLKPLLDIV_MASK ; 
 scalar_t__ PRCM_SEM ; 
 int PRCM_SEM_PRCM_SEM ; 
 int PRCM_SGACLK_MGT_SGACLKDIV_BY_2_5_EN ; 
 TYPE_1__* clk_mgt ; 
 int /*<<< orphan*/  clk_mgt_lock ; 
 int clock_divider (unsigned long,unsigned long) ; 
 unsigned long clock_source_rate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  do_div (unsigned long,int) ; 
 int min (int,int) ; 
 scalar_t__ prcmu_base ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void set_clock_rate(u8 clock, unsigned long rate)
{
	u32 val;
	u32 div;
	unsigned long src_rate;
	unsigned long flags;

	spin_lock_irqsave(&clk_mgt_lock, flags);

	/* Grab the HW semaphore. */
	while ((readl(PRCM_SEM) & PRCM_SEM_PRCM_SEM) != 0)
		cpu_relax();

	val = readl(prcmu_base + clk_mgt[clock].offset);
	src_rate = clock_source_rate((val | clk_mgt[clock].pllsw),
		clk_mgt[clock].branch);
	div = clock_divider(src_rate, rate);
	if (val & PRCM_CLK_MGT_CLK38) {
		if (clk_mgt[clock].clk38div) {
			if (div > 1)
				val |= PRCM_CLK_MGT_CLK38DIV;
			else
				val &= ~PRCM_CLK_MGT_CLK38DIV;
		}
	} else if (clock == PRCMU_SGACLK) {
		val &= ~(PRCM_CLK_MGT_CLKPLLDIV_MASK |
			PRCM_SGACLK_MGT_SGACLKDIV_BY_2_5_EN);
		if (div == 3) {
			u64 r = (src_rate * 10);

			(void)do_div(r, 25);
			if (r <= rate) {
				val |= PRCM_SGACLK_MGT_SGACLKDIV_BY_2_5_EN;
				div = 0;
			}
		}
		val |= min(div, (u32)31);
	} else {
		val &= ~PRCM_CLK_MGT_CLKPLLDIV_MASK;
		val |= min(div, (u32)31);
	}
	writel(val, prcmu_base + clk_mgt[clock].offset);

	/* Release the HW semaphore. */
	writel(0, PRCM_SEM);

	spin_unlock_irqrestore(&clk_mgt_lock, flags);
}