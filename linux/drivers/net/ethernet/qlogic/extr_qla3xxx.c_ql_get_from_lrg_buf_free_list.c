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
struct ql_rcv_buf_cb {struct ql_rcv_buf_cb* next; } ;
struct ql3_adapter {int /*<<< orphan*/  lrg_buf_free_count; int /*<<< orphan*/ * lrg_buf_free_tail; struct ql_rcv_buf_cb* lrg_buf_free_head; } ;

/* Variables and functions */

__attribute__((used)) static struct ql_rcv_buf_cb *ql_get_from_lrg_buf_free_list(struct ql3_adapter
							   *qdev)
{
	struct ql_rcv_buf_cb *lrg_buf_cb = qdev->lrg_buf_free_head;

	if (lrg_buf_cb != NULL) {
		qdev->lrg_buf_free_head = lrg_buf_cb->next;
		if (qdev->lrg_buf_free_head == NULL)
			qdev->lrg_buf_free_tail = NULL;
		qdev->lrg_buf_free_count--;
	}

	return lrg_buf_cb;
}