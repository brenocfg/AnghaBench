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
struct dwc3 {scalar_t__ revision; int fladj; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GFLADJ ; 
 int DWC3_GFLADJ_30MHZ_MASK ; 
 int DWC3_GFLADJ_30MHZ_SDBND_SEL ; 
 scalar_t__ DWC3_REVISION_250A ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc3_frame_length_adjustment(struct dwc3 *dwc)
{
	u32 reg;
	u32 dft;

	if (dwc->revision < DWC3_REVISION_250A)
		return;

	if (dwc->fladj == 0)
		return;

	reg = dwc3_readl(dwc->regs, DWC3_GFLADJ);
	dft = reg & DWC3_GFLADJ_30MHZ_MASK;
	if (dft != dwc->fladj) {
		reg &= ~DWC3_GFLADJ_30MHZ_MASK;
		reg |= DWC3_GFLADJ_30MHZ_SDBND_SEL | dwc->fladj;
		dwc3_writel(dwc->regs, DWC3_GFLADJ, reg);
	}
}