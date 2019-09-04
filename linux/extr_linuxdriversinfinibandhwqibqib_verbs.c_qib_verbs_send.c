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
struct rvt_sge_state {int dummy; } ;
struct TYPE_2__ {scalar_t__ qp_type; int /*<<< orphan*/  device; } ;
struct rvt_qp {TYPE_1__ ibqp; } ;
struct qib_devdata {int flags; } ;
struct ib_header {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_SMI ; 
 int QIB_HAS_SEND_DMA ; 
 struct qib_devdata* dd_from_ibdev (int /*<<< orphan*/ ) ; 
 int qib_verbs_send_dma (struct rvt_qp*,struct ib_header*,int,struct rvt_sge_state*,int,int,int) ; 
 int qib_verbs_send_pio (struct rvt_qp*,struct ib_header*,int,struct rvt_sge_state*,int,int,int) ; 

int qib_verbs_send(struct rvt_qp *qp, struct ib_header *hdr,
		   u32 hdrwords, struct rvt_sge_state *ss, u32 len)
{
	struct qib_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	u32 plen;
	int ret;
	u32 dwords = (len + 3) >> 2;

	/*
	 * Calculate the send buffer trigger address.
	 * The +1 counts for the pbc control dword following the pbc length.
	 */
	plen = hdrwords + dwords + 1;

	/*
	 * VL15 packets (IB_QPT_SMI) will always use PIO, so we
	 * can defer SDMA restart until link goes ACTIVE without
	 * worrying about just how we got there.
	 */
	if (qp->ibqp.qp_type == IB_QPT_SMI ||
	    !(dd->flags & QIB_HAS_SEND_DMA))
		ret = qib_verbs_send_pio(qp, hdr, hdrwords, ss, len,
					 plen, dwords);
	else
		ret = qib_verbs_send_dma(qp, hdr, hdrwords, ss, len,
					 plen, dwords);

	return ret;
}