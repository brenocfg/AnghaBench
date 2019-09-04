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
typedef  size_t u16 ;
struct ena_rss {int tbl_log_size; size_t* host_rss_ind_tbl; TYPE_1__* rss_ind_tbl; } ;
struct ena_com_io_sq {scalar_t__ direction; int /*<<< orphan*/  idx; } ;
struct ena_com_dev {struct ena_com_io_sq* io_sq_queues; struct ena_rss rss; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq_idx; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ENA_COM_IO_QUEUE_DIRECTION_RX ; 
 size_t ENA_TOTAL_NUM_QUEUES ; 

__attribute__((used)) static int ena_com_ind_tbl_convert_to_device(struct ena_com_dev *ena_dev)
{
	struct ena_rss *rss = &ena_dev->rss;
	struct ena_com_io_sq *io_sq;
	u16 qid;
	int i;

	for (i = 0; i < 1 << rss->tbl_log_size; i++) {
		qid = rss->host_rss_ind_tbl[i];
		if (qid >= ENA_TOTAL_NUM_QUEUES)
			return -EINVAL;

		io_sq = &ena_dev->io_sq_queues[qid];

		if (io_sq->direction != ENA_COM_IO_QUEUE_DIRECTION_RX)
			return -EINVAL;

		rss->rss_ind_tbl[i].cq_idx = io_sq->idx;
	}

	return 0;
}