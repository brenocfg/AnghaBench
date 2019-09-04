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
typedef  int /*<<< orphan*/  u8 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCCR ; 
 int CCCR_A_BIT ; 
 int CCCR_CPDIS_BIT ; 
 int /*<<< orphan*/  CCSR ; 
 int /*<<< orphan*/  PXA_MEM_13Mhz ; 
 int /*<<< orphan*/  PXA_MEM_RUN ; 
 int /*<<< orphan*/  PXA_MEM_SYSTEM_BUS ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 clk_pxa27x_memory_get_parent(struct clk_hw *hw)
{
	unsigned int osc_forced, a;
	unsigned long cccr = readl(CCCR);
	unsigned long ccsr = readl(CCSR);

	osc_forced = ccsr & (1 << CCCR_CPDIS_BIT);
	a = cccr & (1 << CCCR_A_BIT);
	if (osc_forced)
		return PXA_MEM_13Mhz;
	if (a)
		return PXA_MEM_SYSTEM_BUS;
	else
		return PXA_MEM_RUN;
}