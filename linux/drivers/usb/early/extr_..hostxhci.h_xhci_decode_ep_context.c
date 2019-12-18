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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int CTX_TO_EP_INTERVAL (int) ; 
 int CTX_TO_EP_MAXPSTREAMS (int) ; 
 int CTX_TO_EP_MULT (int) ; 
 int CTX_TO_EP_TYPE (int) ; 
 int CTX_TO_MAX_BURST (int) ; 
 int CTX_TO_MAX_ESIT_PAYLOAD (int) ; 
 int CTX_TO_MAX_ESIT_PAYLOAD_HI (int) ; 
 int EP_AVG_TRB_LENGTH (int) ; 
 int EP_HAS_LSA ; 
 int EP_STATE_MASK ; 
 int MAX_PACKET_DECODED (int) ; 
 int sprintf (char*,char*,...) ; 
 char* xhci_ep_state_string (int) ; 
 char* xhci_ep_type_string (int) ; 

__attribute__((used)) static inline const char *xhci_decode_ep_context(u32 info, u32 info2, u64 deq,
		u32 tx_info)
{
	static char str[1024];
	int ret;

	u32 esit;
	u16 maxp;
	u16 avg;

	u8 max_pstr;
	u8 ep_state;
	u8 interval;
	u8 ep_type;
	u8 burst;
	u8 cerr;
	u8 mult;

	bool lsa;
	bool hid;

	esit = CTX_TO_MAX_ESIT_PAYLOAD_HI(info) << 16 |
		CTX_TO_MAX_ESIT_PAYLOAD(tx_info);

	ep_state = info & EP_STATE_MASK;
	max_pstr = CTX_TO_EP_MAXPSTREAMS(info);
	interval = CTX_TO_EP_INTERVAL(info);
	mult = CTX_TO_EP_MULT(info) + 1;
	lsa = !!(info & EP_HAS_LSA);

	cerr = (info2 & (3 << 1)) >> 1;
	ep_type = CTX_TO_EP_TYPE(info2);
	hid = !!(info2 & (1 << 7));
	burst = CTX_TO_MAX_BURST(info2);
	maxp = MAX_PACKET_DECODED(info2);

	avg = EP_AVG_TRB_LENGTH(tx_info);

	ret = sprintf(str, "State %s mult %d max P. Streams %d %s",
			xhci_ep_state_string(ep_state), mult,
			max_pstr, lsa ? "LSA " : "");

	ret += sprintf(str + ret, "interval %d us max ESIT payload %d CErr %d ",
			(1 << interval) * 125, esit, cerr);

	ret += sprintf(str + ret, "Type %s %sburst %d maxp %d deq %016llx ",
			xhci_ep_type_string(ep_type), hid ? "HID" : "",
			burst, maxp, deq);

	ret += sprintf(str + ret, "avg trb len %d", avg);

	return str;
}