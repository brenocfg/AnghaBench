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
struct TYPE_2__ {int /*<<< orphan*/  done; } ;
struct iser_rx_desc {int /*<<< orphan*/  rx_sg; TYPE_1__ cqe; } ;
struct ib_conn {int post_recv_buf_count; struct ib_recv_wr* rx_wr; int /*<<< orphan*/  qp; } ;
struct iser_conn {unsigned int rx_desc_head; unsigned int qp_max_recv_dtos_mask; struct iser_rx_desc* rx_descs; struct ib_conn ib_conn; } ;
struct ib_recv_wr {int num_sge; struct ib_recv_wr* next; int /*<<< orphan*/ * sg_list; TYPE_1__* wr_cqe; } ;

/* Variables and functions */
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 
 int /*<<< orphan*/  iser_task_rsp ; 

int iser_post_recvm(struct iser_conn *iser_conn, int count)
{
	struct ib_conn *ib_conn = &iser_conn->ib_conn;
	unsigned int my_rx_head = iser_conn->rx_desc_head;
	struct iser_rx_desc *rx_desc;
	struct ib_recv_wr *wr;
	int i, ib_ret;

	for (wr = ib_conn->rx_wr, i = 0; i < count; i++, wr++) {
		rx_desc = &iser_conn->rx_descs[my_rx_head];
		rx_desc->cqe.done = iser_task_rsp;
		wr->wr_cqe = &rx_desc->cqe;
		wr->sg_list = &rx_desc->rx_sg;
		wr->num_sge = 1;
		wr->next = wr + 1;
		my_rx_head = (my_rx_head + 1) & iser_conn->qp_max_recv_dtos_mask;
	}

	wr--;
	wr->next = NULL; /* mark end of work requests list */

	ib_conn->post_recv_buf_count += count;
	ib_ret = ib_post_recv(ib_conn->qp, ib_conn->rx_wr, NULL);
	if (ib_ret) {
		iser_err("ib_post_recv failed ret=%d\n", ib_ret);
		ib_conn->post_recv_buf_count -= count;
	} else
		iser_conn->rx_desc_head = my_rx_head;

	return ib_ret;
}