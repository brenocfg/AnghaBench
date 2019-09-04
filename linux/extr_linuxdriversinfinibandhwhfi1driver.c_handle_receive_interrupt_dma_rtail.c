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
typedef  scalar_t__ u32 ;
struct hfi1_packet {scalar_t__ rhqoff; } ;
struct hfi1_ctxtdata {scalar_t__ head; } ;

/* Variables and functions */
 int RCV_PKT_DONE ; 
 int RCV_PKT_OK ; 
 int /*<<< orphan*/  finish_packet (struct hfi1_packet*) ; 
 scalar_t__ get_rcvhdrtail (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  init_packet (struct hfi1_ctxtdata*,struct hfi1_packet*) ; 
 int /*<<< orphan*/  prescan_rxq (struct hfi1_ctxtdata*,struct hfi1_packet*) ; 
 int process_rcv_packet (struct hfi1_packet*,int) ; 
 int /*<<< orphan*/  process_rcv_qp_work (struct hfi1_packet*) ; 
 int /*<<< orphan*/  process_rcv_update (int,struct hfi1_packet*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

int handle_receive_interrupt_dma_rtail(struct hfi1_ctxtdata *rcd, int thread)
{
	u32 hdrqtail;
	int last = RCV_PKT_OK;
	struct hfi1_packet packet;

	init_packet(rcd, &packet);
	hdrqtail = get_rcvhdrtail(rcd);
	if (packet.rhqoff == hdrqtail) {
		last = RCV_PKT_DONE;
		goto bail;
	}
	smp_rmb();  /* prevent speculative reads of dma'ed hdrq */

	prescan_rxq(rcd, &packet);

	while (last == RCV_PKT_OK) {
		last = process_rcv_packet(&packet, thread);
		if (packet.rhqoff == hdrqtail)
			last = RCV_PKT_DONE;
		process_rcv_update(last, &packet);
	}
	process_rcv_qp_work(&packet);
	rcd->head = packet.rhqoff;
bail:
	finish_packet(&packet);
	return last;
}