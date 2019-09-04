#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct hfi1_packet {int rhf; void** ebuf; int tlen; int /*<<< orphan*/  hdr; TYPE_1__* rcd; } ;
struct TYPE_4__ {int status_and_code; void* packet_flit2; void* packet_flit1; } ;
struct hfi1_devdata {TYPE_2__ err_info_rcvport; int /*<<< orphan*/  sw_rcv_bypass_packet_errors; } ;
typedef  int /*<<< orphan*/  flits ;
struct TYPE_3__ {struct hfi1_devdata* dd; } ;

/* Variables and functions */
 int BAD_L2_ERR ; 
 int OPA_EI_STATUS_SMASK ; 
 int RHF_LEN_ERR ; 
 int RHF_RCV_CONTINUE ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  handle_eflags (struct hfi1_packet*) ; 
 int hfi1_16B_get_l2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_16B_rcv (struct hfi1_packet*) ; 
 scalar_t__ hfi1_is_vnic_packet (struct hfi1_packet*) ; 
 scalar_t__ hfi1_setup_bypass_packet (struct hfi1_packet*) ; 
 int /*<<< orphan*/  hfi1_vnic_bypass_rcv (struct hfi1_packet*) ; 
 int /*<<< orphan*/  incr_cntr64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhf_err_flags (int) ; 
 int /*<<< orphan*/  trace_hfi1_rcvhdr (struct hfi1_packet*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_receive_bypass(struct hfi1_packet *packet)
{
	struct hfi1_devdata *dd = packet->rcd->dd;

	if (hfi1_is_vnic_packet(packet)) {
		hfi1_vnic_bypass_rcv(packet);
		return RHF_RCV_CONTINUE;
	}

	if (hfi1_setup_bypass_packet(packet))
		return RHF_RCV_CONTINUE;

	trace_hfi1_rcvhdr(packet);

	if (unlikely(rhf_err_flags(packet->rhf))) {
		handle_eflags(packet);
		return RHF_RCV_CONTINUE;
	}

	if (hfi1_16B_get_l2(packet->hdr) == 0x2) {
		hfi1_16B_rcv(packet);
	} else {
		dd_dev_err(dd,
			   "Bypass packets other than 16B are not supported in normal operation. Dropping\n");
		incr_cntr64(&dd->sw_rcv_bypass_packet_errors);
		if (!(dd->err_info_rcvport.status_and_code &
		      OPA_EI_STATUS_SMASK)) {
			u64 *flits = packet->ebuf;

			if (flits && !(packet->rhf & RHF_LEN_ERR)) {
				dd->err_info_rcvport.packet_flit1 = flits[0];
				dd->err_info_rcvport.packet_flit2 =
					packet->tlen > sizeof(flits[0]) ?
					flits[1] : 0;
			}
			dd->err_info_rcvport.status_and_code |=
				(OPA_EI_STATUS_SMASK | BAD_L2_ERR);
		}
	}
	return RHF_RCV_CONTINUE;
}