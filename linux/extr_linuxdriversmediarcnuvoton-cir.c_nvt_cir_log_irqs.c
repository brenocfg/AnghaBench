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

/* Variables and functions */
 int CIR_IRSTS_GH ; 
 int CIR_IRSTS_PE ; 
 int CIR_IRSTS_RDR ; 
 int CIR_IRSTS_RFO ; 
 int CIR_IRSTS_RTR ; 
 int CIR_IRSTS_TE ; 
 int CIR_IRSTS_TFU ; 
 int CIR_IRSTS_TTR ; 
 int /*<<< orphan*/  nvt_dbg (char*,int,int,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void nvt_cir_log_irqs(u8 status, u8 iren)
{
	nvt_dbg("IRQ 0x%02x (IREN 0x%02x) :%s%s%s%s%s%s%s%s%s",
		status, iren,
		status & CIR_IRSTS_RDR	? " RDR"	: "",
		status & CIR_IRSTS_RTR	? " RTR"	: "",
		status & CIR_IRSTS_PE	? " PE"		: "",
		status & CIR_IRSTS_RFO	? " RFO"	: "",
		status & CIR_IRSTS_TE	? " TE"		: "",
		status & CIR_IRSTS_TTR	? " TTR"	: "",
		status & CIR_IRSTS_TFU	? " TFU"	: "",
		status & CIR_IRSTS_GH	? " GH"		: "",
		status & ~(CIR_IRSTS_RDR | CIR_IRSTS_RTR | CIR_IRSTS_PE |
			   CIR_IRSTS_RFO | CIR_IRSTS_TE | CIR_IRSTS_TTR |
			   CIR_IRSTS_TFU | CIR_IRSTS_GH) ? " ?" : "");
}