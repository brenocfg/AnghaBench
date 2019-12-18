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
struct bcm_kona_usb {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ OTGCTL ; 
 int OTGCTL_HRESET_N ; 
 int OTGCTL_OTGSTAT1 ; 
 int OTGCTL_OTGSTAT2 ; 
 int OTGCTL_PRST_N_SW ; 
 int OTGCTL_UTMI_LINE_STATE0 ; 
 int OTGCTL_UTMI_LINE_STATE1 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void bcm_kona_usb_phy_power(struct bcm_kona_usb *phy, int on)
{
	u32 val;

	val = readl(phy->regs + OTGCTL);
	if (on) {
		/* Configure and power PHY */
		val &= ~(OTGCTL_OTGSTAT2 | OTGCTL_OTGSTAT1 |
			 OTGCTL_UTMI_LINE_STATE1 | OTGCTL_UTMI_LINE_STATE0);
		val |= OTGCTL_PRST_N_SW | OTGCTL_HRESET_N;
	} else {
		val &= ~(OTGCTL_PRST_N_SW | OTGCTL_HRESET_N);
	}
	writel(val, phy->regs + OTGCTL);
}