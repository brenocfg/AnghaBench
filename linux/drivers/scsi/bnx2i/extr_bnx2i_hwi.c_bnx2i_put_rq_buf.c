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
typedef  int u16 ;
struct TYPE_6__ {int rq_prod_idx; int rqe_left; scalar_t__ ctx_base; scalar_t__ rq_pgtbl_virt; } ;
struct bnx2i_endpoint {TYPE_3__ qp; TYPE_2__* hba; } ;
struct bnx2i_conn {TYPE_1__* hba; struct bnx2i_endpoint* ep; } ;
struct bnx2i_5771x_sq_rq_db {int prod_idx; } ;
struct TYPE_5__ {int /*<<< orphan*/  cnic_dev_type; } ;
struct TYPE_4__ {int max_rqes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2I_NX2_DEV_57710 ; 
 scalar_t__ CNIC_RECV_DOORBELL ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

void bnx2i_put_rq_buf(struct bnx2i_conn *bnx2i_conn, int count)
{
	struct bnx2i_5771x_sq_rq_db *rq_db;
	u16 hi_bit = (bnx2i_conn->ep->qp.rq_prod_idx & 0x8000);
	struct bnx2i_endpoint *ep = bnx2i_conn->ep;

	ep->qp.rqe_left += count;
	ep->qp.rq_prod_idx &= 0x7FFF;
	ep->qp.rq_prod_idx += count;

	if (ep->qp.rq_prod_idx > bnx2i_conn->hba->max_rqes) {
		ep->qp.rq_prod_idx %= bnx2i_conn->hba->max_rqes;
		if (!hi_bit)
			ep->qp.rq_prod_idx |= 0x8000;
	} else
		ep->qp.rq_prod_idx |= hi_bit;

	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type)) {
		rq_db = (struct bnx2i_5771x_sq_rq_db *) ep->qp.rq_pgtbl_virt;
		rq_db->prod_idx = ep->qp.rq_prod_idx;
		/* no need to ring hardware doorbell for 57710 */
	} else {
		writew(ep->qp.rq_prod_idx,
		       ep->qp.ctx_base + CNIC_RECV_DOORBELL);
	}
}