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
struct hfi1_ctxtdata {scalar_t__ seq_cnt; scalar_t__ head; int /*<<< orphan*/  ctxt; int /*<<< orphan*/  dd; int /*<<< orphan*/  rcvhdrtail_kvaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCV_HDR_TAIL ; 
 scalar_t__ get_rcvhdrtail (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  get_rhf_addr (struct hfi1_ctxtdata*) ; 
 scalar_t__ read_uctxt_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rhf_rcv_seq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhf_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int check_packet_present(struct hfi1_ctxtdata *rcd)
{
	u32 tail;
	int present;

	if (!rcd->rcvhdrtail_kvaddr)
		present = (rcd->seq_cnt ==
				rhf_rcv_seq(rhf_to_cpu(get_rhf_addr(rcd))));
	else /* is RDMA rtail */
		present = (rcd->head != get_rcvhdrtail(rcd));

	if (present)
		return 1;

	/* fall back to a CSR read, correct indpendent of DMA_RTAIL */
	tail = (u32)read_uctxt_csr(rcd->dd, rcd->ctxt, RCV_HDR_TAIL);
	return rcd->head != tail;
}