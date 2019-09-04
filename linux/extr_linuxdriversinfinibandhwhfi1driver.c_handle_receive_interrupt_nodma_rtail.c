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
struct hfi1_packet {int /*<<< orphan*/  rhqoff; int /*<<< orphan*/  rhf; } ;
struct hfi1_ctxtdata {int seq_cnt; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int RCV_PKT_DONE ; 
 int RCV_PKT_OK ; 
 int /*<<< orphan*/  finish_packet (struct hfi1_packet*) ; 
 int /*<<< orphan*/  init_packet (struct hfi1_ctxtdata*,struct hfi1_packet*) ; 
 int /*<<< orphan*/  prescan_rxq (struct hfi1_ctxtdata*,struct hfi1_packet*) ; 
 int process_rcv_packet (struct hfi1_packet*,int) ; 
 int /*<<< orphan*/  process_rcv_qp_work (struct hfi1_packet*) ; 
 int /*<<< orphan*/  process_rcv_update (int,struct hfi1_packet*) ; 
 int rhf_rcv_seq (int /*<<< orphan*/ ) ; 

int handle_receive_interrupt_nodma_rtail(struct hfi1_ctxtdata *rcd, int thread)
{
	u32 seq;
	int last = RCV_PKT_OK;
	struct hfi1_packet packet;

	init_packet(rcd, &packet);
	seq = rhf_rcv_seq(packet.rhf);
	if (seq != rcd->seq_cnt) {
		last = RCV_PKT_DONE;
		goto bail;
	}

	prescan_rxq(rcd, &packet);

	while (last == RCV_PKT_OK) {
		last = process_rcv_packet(&packet, thread);
		seq = rhf_rcv_seq(packet.rhf);
		if (++rcd->seq_cnt > 13)
			rcd->seq_cnt = 1;
		if (seq != rcd->seq_cnt)
			last = RCV_PKT_DONE;
		process_rcv_update(last, &packet);
	}
	process_rcv_qp_work(&packet);
	rcd->head = packet.rhqoff;
bail:
	finish_packet(&packet);
	return last;
}