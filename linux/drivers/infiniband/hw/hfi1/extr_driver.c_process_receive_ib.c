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
struct hfi1_packet {int /*<<< orphan*/  rhf; } ;

/* Variables and functions */
 int RHF_RCV_CONTINUE ; 
 int /*<<< orphan*/  handle_eflags (struct hfi1_packet*) ; 
 int /*<<< orphan*/  hfi1_dbg_should_fault_rx (struct hfi1_packet*) ; 
 int /*<<< orphan*/  hfi1_ib_rcv (struct hfi1_packet*) ; 
 scalar_t__ hfi1_setup_9B_packet (struct hfi1_packet*) ; 
 int /*<<< orphan*/  rhf_err_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_rcvhdr (struct hfi1_packet*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_receive_ib(struct hfi1_packet *packet)
{
	if (hfi1_setup_9B_packet(packet))
		return RHF_RCV_CONTINUE;

	if (unlikely(hfi1_dbg_should_fault_rx(packet)))
		return RHF_RCV_CONTINUE;

	trace_hfi1_rcvhdr(packet);

	if (unlikely(rhf_err_flags(packet->rhf))) {
		handle_eflags(packet);
		return RHF_RCV_CONTINUE;
	}

	hfi1_ib_rcv(packet);
	return RHF_RCV_CONTINUE;
}