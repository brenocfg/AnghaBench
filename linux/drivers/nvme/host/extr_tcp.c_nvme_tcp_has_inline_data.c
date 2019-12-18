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
struct request {int dummy; } ;
struct nvme_tcp_request {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 scalar_t__ WRITE ; 
 struct request* blk_mq_rq_from_pdu (struct nvme_tcp_request*) ; 
 unsigned int blk_rq_payload_bytes (struct request*) ; 
 int /*<<< orphan*/  nvme_tcp_async_req (struct nvme_tcp_request*) ; 
 unsigned int nvme_tcp_inline_data_size (int /*<<< orphan*/ ) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool nvme_tcp_has_inline_data(struct nvme_tcp_request *req)
{
	struct request *rq;
	unsigned int bytes;

	if (unlikely(nvme_tcp_async_req(req)))
		return false; /* async events don't have a request */

	rq = blk_mq_rq_from_pdu(req);
	bytes = blk_rq_payload_bytes(rq);

	return rq_data_dir(rq) == WRITE && bytes &&
		bytes <= nvme_tcp_inline_data_size(req->queue);
}