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
struct isert_conn {int /*<<< orphan*/  qp; } ;
struct iser_rx_desc {int in_use; int /*<<< orphan*/  rx_sg; int /*<<< orphan*/  rx_cqe; } ;
struct ib_recv_wr {int num_sge; int /*<<< orphan*/ * next; int /*<<< orphan*/ * sg_list; int /*<<< orphan*/ * wr_cqe; } ;

/* Variables and functions */
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isert_err (char*,int) ; 

__attribute__((used)) static int
isert_post_recv(struct isert_conn *isert_conn, struct iser_rx_desc *rx_desc)
{
	struct ib_recv_wr rx_wr;
	int ret;

	if (!rx_desc->in_use) {
		/*
		 * if the descriptor is not in-use we already reposted it
		 * for recv, so just silently return
		 */
		return 0;
	}

	rx_desc->in_use = false;
	rx_wr.wr_cqe = &rx_desc->rx_cqe;
	rx_wr.sg_list = &rx_desc->rx_sg;
	rx_wr.num_sge = 1;
	rx_wr.next = NULL;

	ret = ib_post_recv(isert_conn->qp, &rx_wr, NULL);
	if (ret)
		isert_err("ib_post_recv() failed with ret: %d\n", ret);

	return ret;
}