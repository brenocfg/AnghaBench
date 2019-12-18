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
struct hfi1_packet {int rhf; TYPE_1__* rcd; } ;
struct TYPE_4__ {int /*<<< orphan*/  verbs_dev; } ;
struct TYPE_3__ {TYPE_2__* dd; } ;

/* Variables and functions */
 int RHF_DC_ERR ; 
 int RHF_RCV_CONTINUE ; 
 scalar_t__ RHF_RCV_TYPE_ERROR ; 
 int /*<<< orphan*/  dd_dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  handle_eflags (struct hfi1_packet*) ; 
 scalar_t__ hfi1_dbg_fault_suppress_err (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_setup_ib_header (struct hfi1_packet*) ; 
 int rhf_err_flags (int) ; 
 scalar_t__ rhf_rcv_type_err (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int process_receive_error(struct hfi1_packet *packet)
{
	/* KHdrHCRCErr -- KDETH packet with a bad HCRC */
	if (unlikely(
		 hfi1_dbg_fault_suppress_err(&packet->rcd->dd->verbs_dev) &&
		 (rhf_rcv_type_err(packet->rhf) == RHF_RCV_TYPE_ERROR ||
		  packet->rhf & RHF_DC_ERR)))
		return RHF_RCV_CONTINUE;

	hfi1_setup_ib_header(packet);
	handle_eflags(packet);

	if (unlikely(rhf_err_flags(packet->rhf)))
		dd_dev_err(packet->rcd->dd,
			   "Unhandled error packet received. Dropping.\n");

	return RHF_RCV_CONTINUE;
}