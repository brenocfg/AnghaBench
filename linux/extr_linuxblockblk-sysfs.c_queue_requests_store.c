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
struct request_queue {scalar_t__ request_fn; int /*<<< orphan*/  mq_ops; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long BLKDEV_MIN_RQ ; 
 int EINVAL ; 
 int blk_mq_update_nr_requests (struct request_queue*,unsigned long) ; 
 int blk_update_nr_requests (struct request_queue*,unsigned long) ; 
 int queue_var_store (unsigned long*,char const*,size_t) ; 

__attribute__((used)) static ssize_t
queue_requests_store(struct request_queue *q, const char *page, size_t count)
{
	unsigned long nr;
	int ret, err;

	if (!q->request_fn && !q->mq_ops)
		return -EINVAL;

	ret = queue_var_store(&nr, page, count);
	if (ret < 0)
		return ret;

	if (nr < BLKDEV_MIN_RQ)
		nr = BLKDEV_MIN_RQ;

	if (q->request_fn)
		err = blk_update_nr_requests(q, nr);
	else
		err = blk_mq_update_nr_requests(q, nr);

	if (err)
		return err;

	return ret;
}