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
struct iser_tx_desc {int dummy; } ;
struct iscsi_task {TYPE_1__* hdr; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  wr_cqe; } ;
struct ib_cq {int dummy; } ;
struct TYPE_2__ {scalar_t__ itt; } ;

/* Variables and functions */
 scalar_t__ IB_WC_SUCCESS ; 
 scalar_t__ RESERVED_ITT ; 
 int /*<<< orphan*/  iscsi_put_task (struct iscsi_task*) ; 
 int /*<<< orphan*/  iser_err_comp (struct ib_wc*,char*) ; 
 struct iser_tx_desc* iser_tx (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void iser_ctrl_comp(struct ib_cq *cq, struct ib_wc *wc)
{
	struct iser_tx_desc *desc = iser_tx(wc->wr_cqe);
	struct iscsi_task *task;

	if (unlikely(wc->status != IB_WC_SUCCESS)) {
		iser_err_comp(wc, "control");
		return;
	}

	/* this arithmetic is legal by libiscsi dd_data allocation */
	task = (void *)desc - sizeof(struct iscsi_task);
	if (task->hdr->itt == RESERVED_ITT)
		iscsi_put_task(task);
}