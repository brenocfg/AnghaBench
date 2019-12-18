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
struct xhci_hcd_histb {scalar_t__ ctrl; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int BIT_FREECLK_EXIST ; 
 int BIT_UTMI_8_16 ; 
 int BIT_UTMI_ULPI ; 
 scalar_t__ GRXTHRCFG ; 
 scalar_t__ GTXTHRCFG ; 
 scalar_t__ REG_GUSB2PHYCFG0 ; 
 scalar_t__ REG_GUSB3PIPECTL0 ; 
 int USB3_DEEMPHASIS0 ; 
 int USB3_DEEMPHASIS_MASK ; 
 int USB3_TX_MARGIN1 ; 
 scalar_t__ of_property_match_string (struct device_node*,char*,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int xhci_histb_config(struct xhci_hcd_histb *histb)
{
	struct device_node *np = histb->dev->of_node;
	u32 regval;

	if (of_property_match_string(np, "phys-names", "inno") >= 0) {
		/* USB2 PHY chose ulpi 8bit interface */
		regval = readl(histb->ctrl + REG_GUSB2PHYCFG0);
		regval &= ~BIT_UTMI_ULPI;
		regval &= ~(BIT_UTMI_8_16);
		regval &= ~BIT_FREECLK_EXIST;
		writel(regval, histb->ctrl + REG_GUSB2PHYCFG0);
	}

	if (of_property_match_string(np, "phys-names", "combo") >= 0) {
		/*
		 * write 0x010c0012 to GUSB3PIPECTL0
		 * GUSB3PIPECTL0[5:3] = 010 : Tx Margin = 900mV ,
		 * decrease TX voltage
		 * GUSB3PIPECTL0[2:1] = 01 : Tx Deemphasis = -3.5dB,
		 * refer to xHCI spec
		 */
		regval = readl(histb->ctrl + REG_GUSB3PIPECTL0);
		regval &= ~USB3_DEEMPHASIS_MASK;
		regval |= USB3_DEEMPHASIS0;
		regval |= USB3_TX_MARGIN1;
		writel(regval, histb->ctrl + REG_GUSB3PIPECTL0);
	}

	writel(0x23100000, histb->ctrl + GTXTHRCFG);
	writel(0x23100000, histb->ctrl + GRXTHRCFG);

	return 0;
}