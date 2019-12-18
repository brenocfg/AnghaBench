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
typedef  int u32 ;
struct isert_conn {struct ib_recv_wr* rx_wr; int /*<<< orphan*/  qp; struct iser_rx_desc* rx_descs; } ;
struct iser_rx_desc {int in_use; int /*<<< orphan*/  rx_sg; int /*<<< orphan*/  rx_cqe; } ;
struct ib_recv_wr {int num_sge; struct ib_recv_wr* next; int /*<<< orphan*/ * sg_list; int /*<<< orphan*/ * wr_cqe; } ;

/* Variables and functions */
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isert_err (char*,int) ; 

__attribute__((used)) static int
isert_post_recvm(struct isert_conn *isert_conn, u32 count)
{
	struct ib_recv_wr *rx_wr;
	int i, ret;
	struct iser_rx_desc *rx_desc;

	for (rx_wr = isert_conn->rx_wr, i = 0; i < count; i++, rx_wr++) {
		rx_desc = &isert_conn->rx_descs[i];

		rx_wr->wr_cqe = &rx_desc->rx_cqe;
		rx_wr->sg_list = &rx_desc->rx_sg;
		rx_wr->num_sge = 1;
		rx_wr->next = rx_wr + 1;
		rx_desc->in_use = false;
	}
	rx_wr--;
	rx_wr->next = NULL; /* mark end of work requests list */

	ret = ib_post_recv(isert_conn->qp, isert_conn->rx_wr, NULL);
	if (ret)
		isert_err("ib_post_recv() failed with ret: %d\n", ret);

	return ret;
}