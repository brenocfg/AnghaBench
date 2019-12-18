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
typedef  int /*<<< orphan*/  u32 ;
struct dwc3_event_depevt {int endpoint_number; int status; int endpoint_event; int parameters; } ;

/* Variables and functions */
#define  DEPEVT_STATUS_CONTROL_DATA 137 
 int DEPEVT_STATUS_CONTROL_PHASE (int) ; 
#define  DEPEVT_STATUS_CONTROL_STATUS 136 
 int DEPEVT_STATUS_IOC ; 
 int DEPEVT_STATUS_LST ; 
 int DEPEVT_STATUS_SHORT ; 
 int DEPEVT_STATUS_TRANSFER_ACTIVE ; 
#define  DEPEVT_STREAMEVT_FOUND 135 
#define  DEPEVT_STREAMEVT_NOTFOUND 134 
#define  DWC3_DEPEVT_EPCMDCMPLT 133 
#define  DWC3_DEPEVT_RXTXFIFOEVT 132 
#define  DWC3_DEPEVT_STREAMEVT 131 
#define  DWC3_DEPEVT_XFERCOMPLETE 130 
#define  DWC3_DEPEVT_XFERINPROGRESS 129 
#define  DWC3_DEPEVT_XFERNOTREADY 128 
 char* dwc3_ep0_state_string (int /*<<< orphan*/ ) ; 
 int snprintf (char*,size_t,char*,...) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static inline const char *dwc3_ep_event_string(char *str, size_t size,
		const struct dwc3_event_depevt *event, u32 ep0state)
{
	u8 epnum = event->endpoint_number;
	size_t len;
	int status;
	int ret;

	ret = snprintf(str, size, "ep%d%s: ", epnum >> 1,
			(epnum & 1) ? "in" : "out");
	if (ret < 0)
		return "UNKNOWN";

	status = event->status;

	switch (event->endpoint_event) {
	case DWC3_DEPEVT_XFERCOMPLETE:
		len = strlen(str);
		snprintf(str + len, size - len, "Transfer Complete (%c%c%c)",
				status & DEPEVT_STATUS_SHORT ? 'S' : 's',
				status & DEPEVT_STATUS_IOC ? 'I' : 'i',
				status & DEPEVT_STATUS_LST ? 'L' : 'l');

		len = strlen(str);

		if (epnum <= 1)
			snprintf(str + len, size - len, " [%s]",
					dwc3_ep0_state_string(ep0state));
		break;
	case DWC3_DEPEVT_XFERINPROGRESS:
		len = strlen(str);

		snprintf(str + len, size - len, "Transfer In Progress [%d] (%c%c%c)",
				event->parameters,
				status & DEPEVT_STATUS_SHORT ? 'S' : 's',
				status & DEPEVT_STATUS_IOC ? 'I' : 'i',
				status & DEPEVT_STATUS_LST ? 'M' : 'm');
		break;
	case DWC3_DEPEVT_XFERNOTREADY:
		len = strlen(str);

		snprintf(str + len, size - len, "Transfer Not Ready [%d]%s",
				event->parameters,
				status & DEPEVT_STATUS_TRANSFER_ACTIVE ?
				" (Active)" : " (Not Active)");

		len = strlen(str);

		/* Control Endpoints */
		if (epnum <= 1) {
			int phase = DEPEVT_STATUS_CONTROL_PHASE(event->status);

			switch (phase) {
			case DEPEVT_STATUS_CONTROL_DATA:
				snprintf(str + ret, size - ret,
						" [Data Phase]");
				break;
			case DEPEVT_STATUS_CONTROL_STATUS:
				snprintf(str + ret, size - ret,
						" [Status Phase]");
			}
		}
		break;
	case DWC3_DEPEVT_RXTXFIFOEVT:
		snprintf(str + ret, size - ret, "FIFO");
		break;
	case DWC3_DEPEVT_STREAMEVT:
		status = event->status;

		switch (status) {
		case DEPEVT_STREAMEVT_FOUND:
			snprintf(str + ret, size - ret, " Stream %d Found",
					event->parameters);
			break;
		case DEPEVT_STREAMEVT_NOTFOUND:
		default:
			snprintf(str + ret, size - ret, " Stream Not Found");
			break;
		}

		break;
	case DWC3_DEPEVT_EPCMDCMPLT:
		snprintf(str + ret, size - ret, "Endpoint Command Complete");
		break;
	default:
		snprintf(str, size, "UNKNOWN");
	}

	return str;
}