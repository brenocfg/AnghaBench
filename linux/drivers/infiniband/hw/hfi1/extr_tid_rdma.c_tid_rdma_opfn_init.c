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
struct tid_rdma_params {int qp; int /*<<< orphan*/  urg; int /*<<< orphan*/  timeout; int /*<<< orphan*/  max_write; int /*<<< orphan*/  max_read; int /*<<< orphan*/  jkey; int /*<<< orphan*/  max_len; } ;
struct rvt_qp {int /*<<< orphan*/  timeout; struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {TYPE_1__* rcd; } ;
struct TYPE_2__ {int ctxt; int /*<<< orphan*/  jkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  TID_RDMA_MAX_READ_SEGS_PER_REQ ; 
 int /*<<< orphan*/  TID_RDMA_MAX_SEGMENT_SIZE ; 
 int /*<<< orphan*/  TID_RDMA_MAX_WRITE_SEGS_PER_REQ ; 
 int /*<<< orphan*/  is_urg_masked (TYPE_1__*) ; 
 int kdeth_qp ; 

void tid_rdma_opfn_init(struct rvt_qp *qp, struct tid_rdma_params *p)
{
	struct hfi1_qp_priv *priv = qp->priv;

	p->qp = (kdeth_qp << 16) | priv->rcd->ctxt;
	p->max_len = TID_RDMA_MAX_SEGMENT_SIZE;
	p->jkey = priv->rcd->jkey;
	p->max_read = TID_RDMA_MAX_READ_SEGS_PER_REQ;
	p->max_write = TID_RDMA_MAX_WRITE_SEGS_PER_REQ;
	p->timeout = qp->timeout;
	p->urg = is_urg_masked(priv->rcd);
}