#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hfi1_packet {size_t opcode; TYPE_2__* rcd; } ;
struct hfi1_ibdev {TYPE_3__* fault; } ;
struct TYPE_6__ {int /*<<< orphan*/ * n_rxfaults; } ;
struct TYPE_5__ {TYPE_1__* dd; } ;
struct TYPE_4__ {struct hfi1_ibdev verbs_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_FAULT_DIR_RX ; 
 scalar_t__ __hfi1_should_fault (struct hfi1_ibdev*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_fault_packet (struct hfi1_packet*) ; 

bool hfi1_dbg_should_fault_rx(struct hfi1_packet *packet)
{
	struct hfi1_ibdev *ibd = &packet->rcd->dd->verbs_dev;

	if (__hfi1_should_fault(ibd, packet->opcode, HFI1_FAULT_DIR_RX)) {
		trace_hfi1_fault_packet(packet);
		ibd->fault->n_rxfaults[packet->opcode]++;
		return true;
	}
	return false;
}