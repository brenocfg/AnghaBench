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
typedef  int u32 ;
struct ocrdma_sge {int /*<<< orphan*/  len; int /*<<< orphan*/  lrkey; int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; } ;
struct ocrdma_qp {int dummy; } ;
struct ocrdma_hdr_wqe {int /*<<< orphan*/  total_len; } ;
struct ib_send_wr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;

/* Variables and functions */
 int ocrdma_build_inline_sges (struct ocrdma_qp*,struct ocrdma_hdr_wqe*,struct ocrdma_sge*,struct ib_send_wr const*,int) ; 
 TYPE_1__* rdma_wr (struct ib_send_wr const*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocrdma_build_write(struct ocrdma_qp *qp, struct ocrdma_hdr_wqe *hdr,
			      const struct ib_send_wr *wr)
{
	int status;
	struct ocrdma_sge *ext_rw = (struct ocrdma_sge *)(hdr + 1);
	struct ocrdma_sge *sge = ext_rw + 1;
	u32 wqe_size = sizeof(*hdr) + sizeof(*ext_rw);

	status = ocrdma_build_inline_sges(qp, hdr, sge, wr, wqe_size);
	if (status)
		return status;
	ext_rw->addr_lo = rdma_wr(wr)->remote_addr;
	ext_rw->addr_hi = upper_32_bits(rdma_wr(wr)->remote_addr);
	ext_rw->lrkey = rdma_wr(wr)->rkey;
	ext_rw->len = hdr->total_len;
	return 0;
}