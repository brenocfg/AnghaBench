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
struct ohci_hcd {int num_ports; } ;

/* Variables and functions */
 int RH_A_DT ; 
 int RH_A_NDP ; 
 int RH_A_NOCP ; 
 int RH_A_NPS ; 
 int RH_A_OCPM ; 
 int RH_A_POTPGT ; 
 int RH_A_PSM ; 
 int RH_B_DR ; 
 int RH_B_PPCM ; 
 int RH_HS_CRWE ; 
 int RH_HS_DRWE ; 
 int RH_HS_LPS ; 
 int RH_HS_LPSC ; 
 int RH_HS_OCI ; 
 int RH_HS_OCIC ; 
 int /*<<< orphan*/  dbg_port_sw (struct ohci_hcd*,int,int,char**,unsigned int*) ; 
 int /*<<< orphan*/  ohci_dbg_sw (struct ohci_hcd*,char**,unsigned int*,char*,int,...) ; 
 int roothub_a (struct ohci_hcd*) ; 
 int roothub_b (struct ohci_hcd*) ; 
 int roothub_portstatus (struct ohci_hcd*,int) ; 
 int roothub_status (struct ohci_hcd*) ; 

__attribute__((used)) static void
ohci_dump_roothub (
	struct ohci_hcd *controller,
	int verbose,
	char **next,
	unsigned *size)
{
	u32			temp, i;

	temp = roothub_a (controller);
	if (temp == ~(u32)0)
		return;

	if (verbose) {
		ohci_dbg_sw (controller, next, size,
			"roothub.a %08x POTPGT=%d%s%s%s%s%s NDP=%d(%d)\n", temp,
			((temp & RH_A_POTPGT) >> 24) & 0xff,
			(temp & RH_A_NOCP) ? " NOCP" : "",
			(temp & RH_A_OCPM) ? " OCPM" : "",
			(temp & RH_A_DT) ? " DT" : "",
			(temp & RH_A_NPS) ? " NPS" : "",
			(temp & RH_A_PSM) ? " PSM" : "",
			(temp & RH_A_NDP), controller->num_ports
			);
		temp = roothub_b (controller);
		ohci_dbg_sw (controller, next, size,
			"roothub.b %08x PPCM=%04x DR=%04x\n",
			temp,
			(temp & RH_B_PPCM) >> 16,
			(temp & RH_B_DR)
			);
		temp = roothub_status (controller);
		ohci_dbg_sw (controller, next, size,
			"roothub.status %08x%s%s%s%s%s%s\n",
			temp,
			(temp & RH_HS_CRWE) ? " CRWE" : "",
			(temp & RH_HS_OCIC) ? " OCIC" : "",
			(temp & RH_HS_LPSC) ? " LPSC" : "",
			(temp & RH_HS_DRWE) ? " DRWE" : "",
			(temp & RH_HS_OCI) ? " OCI" : "",
			(temp & RH_HS_LPS) ? " LPS" : ""
			);
	}

	for (i = 0; i < controller->num_ports; i++) {
		temp = roothub_portstatus (controller, i);
		dbg_port_sw (controller, i, temp, next, size);
	}
}