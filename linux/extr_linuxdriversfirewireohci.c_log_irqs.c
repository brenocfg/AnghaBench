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
struct fw_ohci {int dummy; } ;

/* Variables and functions */
 int OHCI1394_RQPkt ; 
 int OHCI1394_RSPkt ; 
 int OHCI1394_busReset ; 
 int OHCI1394_cycle64Seconds ; 
 int OHCI1394_cycleInconsistent ; 
 int OHCI1394_cycleTooLong ; 
 int OHCI1394_isochRx ; 
 int OHCI1394_isochTx ; 
 int OHCI1394_postedWriteErr ; 
 int OHCI1394_regAccessFail ; 
 int OHCI1394_reqTxComplete ; 
 int OHCI1394_respTxComplete ; 
 int OHCI1394_selfIDComplete ; 
 int OHCI1394_unrecoverableError ; 
 int OHCI_PARAM_DEBUG_BUSRESETS ; 
 int OHCI_PARAM_DEBUG_IRQS ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ohci_notice (struct fw_ohci*,char*,int,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int param_debug ; 

__attribute__((used)) static void log_irqs(struct fw_ohci *ohci, u32 evt)
{
	if (likely(!(param_debug &
			(OHCI_PARAM_DEBUG_IRQS | OHCI_PARAM_DEBUG_BUSRESETS))))
		return;

	if (!(param_debug & OHCI_PARAM_DEBUG_IRQS) &&
	    !(evt & OHCI1394_busReset))
		return;

	ohci_notice(ohci, "IRQ %08x%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", evt,
	    evt & OHCI1394_selfIDComplete	? " selfID"		: "",
	    evt & OHCI1394_RQPkt		? " AR_req"		: "",
	    evt & OHCI1394_RSPkt		? " AR_resp"		: "",
	    evt & OHCI1394_reqTxComplete	? " AT_req"		: "",
	    evt & OHCI1394_respTxComplete	? " AT_resp"		: "",
	    evt & OHCI1394_isochRx		? " IR"			: "",
	    evt & OHCI1394_isochTx		? " IT"			: "",
	    evt & OHCI1394_postedWriteErr	? " postedWriteErr"	: "",
	    evt & OHCI1394_cycleTooLong		? " cycleTooLong"	: "",
	    evt & OHCI1394_cycle64Seconds	? " cycle64Seconds"	: "",
	    evt & OHCI1394_cycleInconsistent	? " cycleInconsistent"	: "",
	    evt & OHCI1394_regAccessFail	? " regAccessFail"	: "",
	    evt & OHCI1394_unrecoverableError	? " unrecoverableError"	: "",
	    evt & OHCI1394_busReset		? " busReset"		: "",
	    evt & ~(OHCI1394_selfIDComplete | OHCI1394_RQPkt |
		    OHCI1394_RSPkt | OHCI1394_reqTxComplete |
		    OHCI1394_respTxComplete | OHCI1394_isochRx |
		    OHCI1394_isochTx | OHCI1394_postedWriteErr |
		    OHCI1394_cycleTooLong | OHCI1394_cycle64Seconds |
		    OHCI1394_cycleInconsistent |
		    OHCI1394_regAccessFail | OHCI1394_busReset)
						? " ?"			: "");
}