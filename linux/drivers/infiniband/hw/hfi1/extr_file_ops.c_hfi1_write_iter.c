#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kiocb {TYPE_1__* ki_filp; } ;
struct iovec {int dummy; } ;
struct iov_iter {unsigned long nr_segs; scalar_t__ iov; } ;
struct hfi1_user_sdma_pkt_q {scalar_t__ n_max_reqs; int /*<<< orphan*/  n_reqs; } ;
struct hfi1_user_sdma_comp_q {int dummy; } ;
struct hfi1_filedata {int /*<<< orphan*/  subctxt; TYPE_2__* uctxt; int /*<<< orphan*/  dd; struct hfi1_user_sdma_comp_q* cq; struct hfi1_user_sdma_pkt_q* pq; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  ctxt; } ;
struct TYPE_3__ {struct hfi1_filedata* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOSPC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int hfi1_user_sdma_process_request (struct hfi1_filedata*,struct iovec*,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  iter_is_iovec (struct iov_iter*) ; 
 int /*<<< orphan*/  trace_hfi1_sdma_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static ssize_t hfi1_write_iter(struct kiocb *kiocb, struct iov_iter *from)
{
	struct hfi1_filedata *fd = kiocb->ki_filp->private_data;
	struct hfi1_user_sdma_pkt_q *pq = fd->pq;
	struct hfi1_user_sdma_comp_q *cq = fd->cq;
	int done = 0, reqs = 0;
	unsigned long dim = from->nr_segs;

	if (!cq || !pq)
		return -EIO;

	if (!iter_is_iovec(from) || !dim)
		return -EINVAL;

	trace_hfi1_sdma_request(fd->dd, fd->uctxt->ctxt, fd->subctxt, dim);

	if (atomic_read(&pq->n_reqs) == pq->n_max_reqs)
		return -ENOSPC;

	while (dim) {
		int ret;
		unsigned long count = 0;

		ret = hfi1_user_sdma_process_request(
			fd, (struct iovec *)(from->iov + done),
			dim, &count);
		if (ret) {
			reqs = ret;
			break;
		}
		dim -= count;
		done += count;
		reqs++;
	}

	return reqs;
}