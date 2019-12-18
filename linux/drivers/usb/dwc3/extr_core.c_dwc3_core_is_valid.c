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
struct dwc3 {int revision; int /*<<< orphan*/  regs; void* version_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GSNPSID ; 
 int DWC3_GSNPSID_MASK ; 
 int DWC3_REVISION_IS_DWC31 ; 
 int /*<<< orphan*/  DWC3_VER_NUMBER ; 
 int /*<<< orphan*/  DWC3_VER_TYPE ; 
 void* dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dwc3_core_is_valid(struct dwc3 *dwc)
{
	u32 reg;

	reg = dwc3_readl(dwc->regs, DWC3_GSNPSID);

	/* This should read as U3 followed by revision number */
	if ((reg & DWC3_GSNPSID_MASK) == 0x55330000) {
		/* Detected DWC_usb3 IP */
		dwc->revision = reg;
	} else if ((reg & DWC3_GSNPSID_MASK) == 0x33310000) {
		/* Detected DWC_usb31 IP */
		dwc->revision = dwc3_readl(dwc->regs, DWC3_VER_NUMBER);
		dwc->revision |= DWC3_REVISION_IS_DWC31;
		dwc->version_type = dwc3_readl(dwc->regs, DWC3_VER_TYPE);
	} else {
		return false;
	}

	return true;
}