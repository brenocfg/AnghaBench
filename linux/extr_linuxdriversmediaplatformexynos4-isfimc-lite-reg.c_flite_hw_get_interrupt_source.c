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
struct fimc_lite {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ FLITE_REG_CISTATUS ; 
 int FLITE_REG_CISTATUS_IRQ_MASK ; 
 int readl (scalar_t__) ; 

u32 flite_hw_get_interrupt_source(struct fimc_lite *dev)
{
	u32 intsrc = readl(dev->regs + FLITE_REG_CISTATUS);
	return intsrc & FLITE_REG_CISTATUS_IRQ_MASK;
}