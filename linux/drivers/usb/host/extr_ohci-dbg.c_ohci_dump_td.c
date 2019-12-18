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
typedef  int u16 ;
struct td {int /*<<< orphan*/  hwBE; int /*<<< orphan*/  hwCBP; int /*<<< orphan*/  hwNextTD; int /*<<< orphan*/  index; int /*<<< orphan*/  urb; int /*<<< orphan*/  hwINFO; } ;
struct ohci_hcd {int dummy; } ;

/* Variables and functions */
 unsigned int MAXPSW ; 
 int /*<<< orphan*/  TD_CC_GET (int) ; 
 int TD_DI ; 
 int TD_DONE ; 
 int TD_DP ; 
#define  TD_DP_IN 133 
#define  TD_DP_OUT 132 
#define  TD_DP_SETUP 131 
 int TD_ISO ; 
 int TD_R ; 
 int TD_T ; 
#define  TD_T_DATA0 130 
#define  TD_T_DATA1 129 
#define  TD_T_TOGGLE 128 
 char* data0 ; 
 char* data1 ; 
 int hc32_to_cpup (struct ohci_hcd const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_dbg (struct ohci_hcd const*,char*,...) ; 
 int ohci_hwPSW (struct ohci_hcd const*,struct td const*,unsigned int) ; 

__attribute__((used)) static void ohci_dump_td (const struct ohci_hcd *ohci, const char *label,
		const struct td *td)
{
	u32	tmp = hc32_to_cpup (ohci, &td->hwINFO);

	ohci_dbg (ohci, "%s td %p%s; urb %p index %d; hw next td %08x\n",
		label, td,
		(tmp & TD_DONE) ? " (DONE)" : "",
		td->urb, td->index,
		hc32_to_cpup (ohci, &td->hwNextTD));
	if ((tmp & TD_ISO) == 0) {
		const char	*toggle, *pid;
		u32	cbp, be;

		switch (tmp & TD_T) {
		case TD_T_DATA0: toggle = data0; break;
		case TD_T_DATA1: toggle = data1; break;
		case TD_T_TOGGLE: toggle = "(CARRY)"; break;
		default: toggle = "(?)"; break;
		}
		switch (tmp & TD_DP) {
		case TD_DP_SETUP: pid = "SETUP"; break;
		case TD_DP_IN: pid = "IN"; break;
		case TD_DP_OUT: pid = "OUT"; break;
		default: pid = "(bad pid)"; break;
		}
		ohci_dbg (ohci, "     info %08x CC=%x %s DI=%d %s %s\n", tmp,
			TD_CC_GET(tmp), /* EC, */ toggle,
			(tmp & TD_DI) >> 21, pid,
			(tmp & TD_R) ? "R" : "");
		cbp = hc32_to_cpup (ohci, &td->hwCBP);
		be = hc32_to_cpup (ohci, &td->hwBE);
		ohci_dbg (ohci, "     cbp %08x be %08x (len %d)\n", cbp, be,
			cbp ? (be + 1 - cbp) : 0);
	} else {
		unsigned	i;
		ohci_dbg (ohci, "  info %08x CC=%x FC=%d DI=%d SF=%04x\n", tmp,
			TD_CC_GET(tmp),
			(tmp >> 24) & 0x07,
			(tmp & TD_DI) >> 21,
			tmp & 0x0000ffff);
		ohci_dbg (ohci, "  bp0 %08x be %08x\n",
			hc32_to_cpup (ohci, &td->hwCBP) & ~0x0fff,
			hc32_to_cpup (ohci, &td->hwBE));
		for (i = 0; i < MAXPSW; i++) {
			u16	psw = ohci_hwPSW (ohci, td, i);
			int	cc = (psw >> 12) & 0x0f;
			ohci_dbg (ohci, "    psw [%d] = %2x, CC=%x %s=%d\n", i,
				psw, cc,
				(cc >= 0x0e) ? "OFFSET" : "SIZE",
				psw & 0x0fff);
		}
	}
}