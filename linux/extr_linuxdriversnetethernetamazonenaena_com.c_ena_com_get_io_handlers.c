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
typedef  size_t u16 ;
struct ena_com_io_sq {int dummy; } ;
struct ena_com_io_cq {int dummy; } ;
struct ena_com_dev {struct ena_com_io_cq* io_cq_queues; struct ena_com_io_sq* io_sq_queues; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t ENA_TOTAL_NUM_QUEUES ; 
 int /*<<< orphan*/  pr_err (char*,size_t,size_t) ; 

int ena_com_get_io_handlers(struct ena_com_dev *ena_dev, u16 qid,
			    struct ena_com_io_sq **io_sq,
			    struct ena_com_io_cq **io_cq)
{
	if (qid >= ENA_TOTAL_NUM_QUEUES) {
		pr_err("Invalid queue number %d but the max is %d\n", qid,
		       ENA_TOTAL_NUM_QUEUES);
		return -EINVAL;
	}

	*io_sq = &ena_dev->io_sq_queues[qid];
	*io_cq = &ena_dev->io_cq_queues[qid];

	return 0;
}