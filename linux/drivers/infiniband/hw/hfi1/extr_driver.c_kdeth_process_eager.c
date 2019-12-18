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
struct hfi1_packet {struct hfi1_ctxtdata* rcd; int /*<<< orphan*/  rhf; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  ppd; } ;

/* Variables and functions */
 int RHF_RCV_CONTINUE ; 
 int /*<<< orphan*/  hfi1_dbg_should_fault_rx (struct hfi1_packet*) ; 
 scalar_t__ hfi1_handle_kdeth_eflags (struct hfi1_ctxtdata*,int /*<<< orphan*/ ,struct hfi1_packet*) ; 
 int /*<<< orphan*/  hfi1_kdeth_eager_rcv (struct hfi1_packet*) ; 
 int /*<<< orphan*/  hfi1_setup_9B_packet (struct hfi1_packet*) ; 
 int /*<<< orphan*/  rhf_err_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_eflags_errs (struct hfi1_packet*) ; 
 int /*<<< orphan*/  trace_hfi1_rcvhdr (struct hfi1_packet*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdeth_process_eager(struct hfi1_packet *packet)
{
	hfi1_setup_9B_packet(packet);
	if (unlikely(hfi1_dbg_should_fault_rx(packet)))
		return RHF_RCV_CONTINUE;

	trace_hfi1_rcvhdr(packet);
	if (unlikely(rhf_err_flags(packet->rhf))) {
		struct hfi1_ctxtdata *rcd = packet->rcd;

		show_eflags_errs(packet);
		if (hfi1_handle_kdeth_eflags(rcd, rcd->ppd, packet))
			return RHF_RCV_CONTINUE;
	}

	hfi1_kdeth_eager_rcv(packet);
	return RHF_RCV_CONTINUE;
}