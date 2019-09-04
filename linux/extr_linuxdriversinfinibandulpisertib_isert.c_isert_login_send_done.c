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
struct isert_conn {int /*<<< orphan*/  conn; TYPE_2__* cm_id; } ;
struct iser_tx_desc {int dummy; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  wr_cqe; TYPE_1__* qp; } ;
struct ib_device {int dummy; } ;
struct ib_cq {int dummy; } ;
struct TYPE_4__ {struct ib_device* device; } ;
struct TYPE_3__ {struct isert_conn* qp_context; } ;

/* Variables and functions */
 scalar_t__ IB_WC_SUCCESS ; 
 scalar_t__ IB_WC_WR_FLUSH_ERR ; 
 struct iser_tx_desc* cqe_to_tx_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_cause_connection_reinstatement (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isert_print_wc (struct ib_wc*,char*) ; 
 int /*<<< orphan*/  isert_unmap_tx_desc (struct iser_tx_desc*,struct ib_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
isert_login_send_done(struct ib_cq *cq, struct ib_wc *wc)
{
	struct isert_conn *isert_conn = wc->qp->qp_context;
	struct ib_device *ib_dev = isert_conn->cm_id->device;
	struct iser_tx_desc *tx_desc = cqe_to_tx_desc(wc->wr_cqe);

	if (unlikely(wc->status != IB_WC_SUCCESS)) {
		isert_print_wc(wc, "login send");
		if (wc->status != IB_WC_WR_FLUSH_ERR)
			iscsit_cause_connection_reinstatement(isert_conn->conn, 0);
	}

	isert_unmap_tx_desc(tx_desc, ib_dev);
}