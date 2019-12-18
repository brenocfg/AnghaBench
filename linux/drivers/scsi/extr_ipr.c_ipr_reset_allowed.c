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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sense_interrupt_reg; } ;
struct ipr_ioa_cfg {TYPE_1__ regs; } ;

/* Variables and functions */
 int volatile IPR_PCII_CRITICAL_OPERATION ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipr_reset_allowed(struct ipr_ioa_cfg *ioa_cfg)
{
	volatile u32 temp_reg;

	temp_reg = readl(ioa_cfg->regs.sense_interrupt_reg);
	return ((temp_reg & IPR_PCII_CRITICAL_OPERATION) == 0);
}