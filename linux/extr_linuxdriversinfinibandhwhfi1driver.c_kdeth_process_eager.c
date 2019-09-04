#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hfi1_packet {TYPE_1__* rcd; int /*<<< orphan*/  rhf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int RHF_RCV_CONTINUE ; 
 int /*<<< orphan*/  dd_dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  handle_eflags (struct hfi1_packet*) ; 
 int /*<<< orphan*/  hfi1_dbg_should_fault_rx (struct hfi1_packet*) ; 
 int /*<<< orphan*/  hfi1_setup_9B_packet (struct hfi1_packet*) ; 
 int /*<<< orphan*/  rhf_err_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdeth_process_eager(struct hfi1_packet *packet)
{
	hfi1_setup_9B_packet(packet);
	if (unlikely(hfi1_dbg_should_fault_rx(packet)))
		return RHF_RCV_CONTINUE;
	if (unlikely(rhf_err_flags(packet->rhf)))
		handle_eflags(packet);

	dd_dev_err(packet->rcd->dd,
		   "Unhandled eager packet received. Dropping.\n");
	return RHF_RCV_CONTINUE;
}