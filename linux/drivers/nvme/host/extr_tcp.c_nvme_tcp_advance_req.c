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
struct nvme_tcp_request {scalar_t__ data_sent; int pdu_sent; scalar_t__ data_len; TYPE_1__* curr_bio; int /*<<< orphan*/  iter; } ;
struct TYPE_2__ {struct TYPE_2__* bi_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  iov_iter_advance (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iov_iter_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_tcp_init_iter (struct nvme_tcp_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nvme_tcp_advance_req(struct nvme_tcp_request *req,
		int len)
{
	req->data_sent += len;
	req->pdu_sent += len;
	iov_iter_advance(&req->iter, len);
	if (!iov_iter_count(&req->iter) &&
	    req->data_sent < req->data_len) {
		req->curr_bio = req->curr_bio->bi_next;
		nvme_tcp_init_iter(req, WRITE);
	}
}