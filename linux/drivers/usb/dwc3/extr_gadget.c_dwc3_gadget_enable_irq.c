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
struct dwc3 {scalar_t__ revision; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DEVTEN ; 
 int DWC3_DEVTEN_CMDCMPLTEN ; 
 int DWC3_DEVTEN_CONNECTDONEEN ; 
 int DWC3_DEVTEN_DISCONNEVTEN ; 
 int DWC3_DEVTEN_ERRTICERREN ; 
 int DWC3_DEVTEN_EVNTOVERFLOWEN ; 
 int DWC3_DEVTEN_ULSTCNGEN ; 
 int DWC3_DEVTEN_USBRSTEN ; 
 int DWC3_DEVTEN_VNDRDEVTSTRCVEDEN ; 
 int DWC3_DEVTEN_WKUPEVTEN ; 
 scalar_t__ DWC3_REVISION_250A ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc3_gadget_enable_irq(struct dwc3 *dwc)
{
	u32			reg;

	/* Enable all but Start and End of Frame IRQs */
	reg = (DWC3_DEVTEN_VNDRDEVTSTRCVEDEN |
			DWC3_DEVTEN_EVNTOVERFLOWEN |
			DWC3_DEVTEN_CMDCMPLTEN |
			DWC3_DEVTEN_ERRTICERREN |
			DWC3_DEVTEN_WKUPEVTEN |
			DWC3_DEVTEN_CONNECTDONEEN |
			DWC3_DEVTEN_USBRSTEN |
			DWC3_DEVTEN_DISCONNEVTEN);

	if (dwc->revision < DWC3_REVISION_250A)
		reg |= DWC3_DEVTEN_ULSTCNGEN;

	dwc3_writel(dwc->regs, DWC3_DEVTEN, reg);
}