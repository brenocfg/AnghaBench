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
struct TYPE_3__ {scalar_t__ ctx_base; int /*<<< orphan*/  sq_prod_idx; scalar_t__ sq_pgtbl_virt; } ;
struct bnx2i_endpoint {TYPE_1__ qp; TYPE_2__* hba; int /*<<< orphan*/  num_active_cmds; } ;
struct bnx2i_conn {struct bnx2i_endpoint* ep; } ;
struct bnx2i_5771x_sq_rq_db {int /*<<< orphan*/  prod_idx; } ;
struct TYPE_4__ {int /*<<< orphan*/  cnic_dev_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2I_NX2_DEV_57710 ; 
 scalar_t__ CNIC_SEND_DOORBELL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2i_ring_577xx_doorbell (struct bnx2i_conn*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void bnx2i_ring_sq_dbell(struct bnx2i_conn *bnx2i_conn, int count)
{
	struct bnx2i_5771x_sq_rq_db *sq_db;
	struct bnx2i_endpoint *ep = bnx2i_conn->ep;

	atomic_inc(&ep->num_active_cmds);
	wmb();	/* flush SQ WQE memory before the doorbell is rung */
	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type)) {
		sq_db = (struct bnx2i_5771x_sq_rq_db *) ep->qp.sq_pgtbl_virt;
		sq_db->prod_idx = ep->qp.sq_prod_idx;
		bnx2i_ring_577xx_doorbell(bnx2i_conn);
	} else
		writew(count, ep->qp.ctx_base + CNIC_SEND_DOORBELL);
}