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
struct TYPE_2__ {scalar_t__ protocol; int clkdel; int sctrl; int states; } ;
struct hfc_pci {TYPE_1__ hw; } ;

/* Variables and functions */
 int CLKDEL_NT ; 
 int CLKDEL_TE ; 
 int /*<<< orphan*/  HFCPCI_CLKDEL ; 
 int HFCPCI_LOAD_STATE ; 
 int /*<<< orphan*/  HFCPCI_SCTRL ; 
 int /*<<< orphan*/  HFCPCI_STATES ; 
 scalar_t__ ISDN_P_NT_S0 ; 
 int SCTRL_MODE_NT ; 
 int /*<<< orphan*/  Write_hfc (struct hfc_pci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
hfcpci_setmode(struct hfc_pci *hc)
{
	if (hc->hw.protocol == ISDN_P_NT_S0) {
		hc->hw.clkdel = CLKDEL_NT;	/* ST-Bit delay for NT-Mode */
		hc->hw.sctrl |= SCTRL_MODE_NT;	/* NT-MODE */
		hc->hw.states = 1;		/* G1 */
	} else {
		hc->hw.clkdel = CLKDEL_TE;	/* ST-Bit delay for TE-Mode */
		hc->hw.sctrl &= ~SCTRL_MODE_NT;	/* TE-MODE */
		hc->hw.states = 2;		/* F2 */
	}
	Write_hfc(hc, HFCPCI_CLKDEL, hc->hw.clkdel);
	Write_hfc(hc, HFCPCI_STATES, HFCPCI_LOAD_STATE | hc->hw.states);
	udelay(10);
	Write_hfc(hc, HFCPCI_STATES, hc->hw.states | 0x40); /* Deactivate */
	Write_hfc(hc, HFCPCI_SCTRL, hc->hw.sctrl);
}