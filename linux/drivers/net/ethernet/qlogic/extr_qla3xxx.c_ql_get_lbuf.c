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
struct ql_rcv_buf_cb {int dummy; } ;
struct ql3_adapter {size_t lrg_buf_index; size_t num_large_buffers; int /*<<< orphan*/  lrg_buf_release_cnt; struct ql_rcv_buf_cb* lrg_buf; } ;

/* Variables and functions */

__attribute__((used)) static struct ql_rcv_buf_cb *ql_get_lbuf(struct ql3_adapter *qdev)
{
	struct ql_rcv_buf_cb *lrg_buf_cb = NULL;
	lrg_buf_cb = &qdev->lrg_buf[qdev->lrg_buf_index];
	qdev->lrg_buf_release_cnt++;
	if (++qdev->lrg_buf_index == qdev->num_large_buffers)
		qdev->lrg_buf_index = 0;
	return lrg_buf_cb;
}