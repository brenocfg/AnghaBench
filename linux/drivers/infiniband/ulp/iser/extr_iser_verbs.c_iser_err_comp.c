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
struct iser_conn {scalar_t__ iscsi_conn; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  vendor_err; TYPE_1__* qp; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_context; } ;

/* Variables and functions */
 scalar_t__ IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  ISCSI_ERR_CONN_FAILED ; 
 int /*<<< orphan*/  ib_wc_status_msg (scalar_t__) ; 
 int /*<<< orphan*/  iscsi_conn_failure (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_dbg (char*,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iser_err (char*,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct iser_conn* to_iser_conn (int /*<<< orphan*/ ) ; 

void iser_err_comp(struct ib_wc *wc, const char *type)
{
	if (wc->status != IB_WC_WR_FLUSH_ERR) {
		struct iser_conn *iser_conn = to_iser_conn(wc->qp->qp_context);

		iser_err("%s failure: %s (%d) vend_err %#x\n", type,
			 ib_wc_status_msg(wc->status), wc->status,
			 wc->vendor_err);

		if (iser_conn->iscsi_conn)
			iscsi_conn_failure(iser_conn->iscsi_conn,
					   ISCSI_ERR_CONN_FAILED);
	} else {
		iser_dbg("%s failure: %s (%d)\n", type,
			 ib_wc_status_msg(wc->status), wc->status);
	}
}