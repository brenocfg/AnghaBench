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
struct usb_hcd {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ RCAR_USB3_CONF1 ; 
 int /*<<< orphan*/  RCAR_USB3_CONF1_VAL ; 
 scalar_t__ RCAR_USB3_CONF2 ; 
 int /*<<< orphan*/  RCAR_USB3_CONF2_VAL ; 
 scalar_t__ RCAR_USB3_CONF3 ; 
 int /*<<< orphan*/  RCAR_USB3_CONF3_VAL ; 
 scalar_t__ RCAR_USB3_LCLK ; 
 int /*<<< orphan*/  RCAR_USB3_LCLK_ENA_VAL ; 
 scalar_t__ RCAR_USB3_RX_POL ; 
 int /*<<< orphan*/  RCAR_USB3_RX_POL_VAL ; 
 scalar_t__ RCAR_USB3_TX_POL ; 
 int /*<<< orphan*/  RCAR_USB3_TX_POL_VAL ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xhci_rcar_start_gen2(struct usb_hcd *hcd)
{
	/* LCLK Select */
	writel(RCAR_USB3_LCLK_ENA_VAL, hcd->regs + RCAR_USB3_LCLK);
	/* USB3.0 Configuration */
	writel(RCAR_USB3_CONF1_VAL, hcd->regs + RCAR_USB3_CONF1);
	writel(RCAR_USB3_CONF2_VAL, hcd->regs + RCAR_USB3_CONF2);
	writel(RCAR_USB3_CONF3_VAL, hcd->regs + RCAR_USB3_CONF3);
	/* USB3.0 Polarity */
	writel(RCAR_USB3_RX_POL_VAL, hcd->regs + RCAR_USB3_RX_POL);
	writel(RCAR_USB3_TX_POL_VAL, hcd->regs + RCAR_USB3_TX_POL);
}