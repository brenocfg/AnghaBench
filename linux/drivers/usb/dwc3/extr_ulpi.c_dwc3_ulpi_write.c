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
typedef  int u32 ;
struct dwc3 {int /*<<< orphan*/  regs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GUSB2PHYACC (int /*<<< orphan*/ ) ; 
 int DWC3_GUSB2PHYACC_NEWREGREQ ; 
 int DWC3_GUSB2PHYACC_WRITE ; 
 int /*<<< orphan*/  DWC3_GUSB2PHYCFG (int /*<<< orphan*/ ) ; 
 int DWC3_GUSB2PHYCFG_SUSPHY ; 
 int DWC3_ULPI_ADDR (int) ; 
 struct dwc3* dev_get_drvdata (struct device*) ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dwc3_ulpi_busyloop (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dwc3_ulpi_write(struct device *dev, u8 addr, u8 val)
{
	struct dwc3 *dwc = dev_get_drvdata(dev);
	u32 reg;

	reg = dwc3_readl(dwc->regs, DWC3_GUSB2PHYCFG(0));
	if (reg & DWC3_GUSB2PHYCFG_SUSPHY) {
		reg &= ~DWC3_GUSB2PHYCFG_SUSPHY;
		dwc3_writel(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);
	}

	reg = DWC3_GUSB2PHYACC_NEWREGREQ | DWC3_ULPI_ADDR(addr);
	reg |= DWC3_GUSB2PHYACC_WRITE | val;
	dwc3_writel(dwc->regs, DWC3_GUSB2PHYACC(0), reg);

	return dwc3_ulpi_busyloop(dwc);
}