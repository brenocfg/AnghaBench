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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCE_INT_MAP ; 
 int CCE_NUM_INT_MAP_CSRS ; 
 int /*<<< orphan*/  PT_INVALID_FLUSH ; 
 int /*<<< orphan*/  RCV_HDR_ADDR ; 
 int /*<<< orphan*/  RCV_HDR_TAIL_ADDR ; 
 scalar_t__ RCV_QP_MAP_TABLE ; 
 scalar_t__ RCV_TID_FLOW_TABLE ; 
 int RXE_NUM_TID_FLOWS ; 
 int /*<<< orphan*/  SEND_CTXT_CREDIT_RETURN_ADDR ; 
 int chip_rcv_array_count (struct hfi1_devdata*) ; 
 int chip_rcv_contexts (struct hfi1_devdata*) ; 
 int chip_send_contexts (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_put_tid (struct hfi1_devdata*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_kctxt_csr (struct hfi1_devdata*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_uctxt_csr (struct hfi1_devdata*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_uninitialized_csrs_and_memories(struct hfi1_devdata *dd)
{
	int i, j;

	/* CceIntMap */
	for (i = 0; i < CCE_NUM_INT_MAP_CSRS; i++)
		write_csr(dd, CCE_INT_MAP + (8 * i), 0);

	/* SendCtxtCreditReturnAddr */
	for (i = 0; i < chip_send_contexts(dd); i++)
		write_kctxt_csr(dd, i, SEND_CTXT_CREDIT_RETURN_ADDR, 0);

	/* PIO Send buffers */
	/* SDMA Send buffers */
	/*
	 * These are not normally read, and (presently) have no method
	 * to be read, so are not pre-initialized
	 */

	/* RcvHdrAddr */
	/* RcvHdrTailAddr */
	/* RcvTidFlowTable */
	for (i = 0; i < chip_rcv_contexts(dd); i++) {
		write_kctxt_csr(dd, i, RCV_HDR_ADDR, 0);
		write_kctxt_csr(dd, i, RCV_HDR_TAIL_ADDR, 0);
		for (j = 0; j < RXE_NUM_TID_FLOWS; j++)
			write_uctxt_csr(dd, i, RCV_TID_FLOW_TABLE + (8 * j), 0);
	}

	/* RcvArray */
	for (i = 0; i < chip_rcv_array_count(dd); i++)
		hfi1_put_tid(dd, i, PT_INVALID_FLUSH, 0, 0);

	/* RcvQPMapTable */
	for (i = 0; i < 32; i++)
		write_csr(dd, RCV_QP_MAP_TABLE + (8 * i), 0);
}