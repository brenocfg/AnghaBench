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
typedef  scalar_t__ u32 ;
struct mcde {scalar_t__ regs; scalar_t__ stride; } ;

/* Variables and functions */
 scalar_t__ MCDE_EXTSRCXA0 ; 
 scalar_t__ MCDE_EXTSRCXA1 ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mcde_set_extsrc(struct mcde *mcde, u32 buffer_address)
{
	/* Write bitmap base address to register */
	writel(buffer_address, mcde->regs + MCDE_EXTSRCXA0);
	/*
	 * Base address for next line this is probably only used
	 * in interlace modes.
	 */
	writel(buffer_address + mcde->stride, mcde->regs + MCDE_EXTSRCXA1);
}