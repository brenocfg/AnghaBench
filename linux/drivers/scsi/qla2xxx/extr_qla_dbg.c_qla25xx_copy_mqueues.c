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
typedef  void* uint32_t ;
struct rsp_que {int length; int /*<<< orphan*/  ring; } ;
struct req_que {int length; int /*<<< orphan*/  ring; } ;
struct qla_hw_data {int max_req_queues; int max_rsp_queues; struct rsp_que** rsp_q_map; struct req_que** req_q_map; int /*<<< orphan*/  mqenable; } ;
struct qla2xxx_mqueue_header {void* size; void* number; void* queue; } ;
struct qla2xxx_mqueue_chain {void* chain_size; void* type; } ;
typedef  int /*<<< orphan*/  response_t ;
typedef  int /*<<< orphan*/  request_t ;

/* Variables and functions */
 int DUMP_CHAIN_QUEUE ; 
 int TYPE_REQUEST_QUEUE ; 
 int TYPE_RESPONSE_QUEUE ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void *
qla25xx_copy_mqueues(struct qla_hw_data *ha, void *ptr, uint32_t **last_chain)
{
	struct qla2xxx_mqueue_chain *q;
	struct qla2xxx_mqueue_header *qh;
	struct req_que *req;
	struct rsp_que *rsp;
	int que;

	if (!ha->mqenable)
		return ptr;

	/* Request queues */
	for (que = 1; que < ha->max_req_queues; que++) {
		req = ha->req_q_map[que];
		if (!req)
			break;

		/* Add chain. */
		q = ptr;
		*last_chain = &q->type;
		q->type = htonl(DUMP_CHAIN_QUEUE);
		q->chain_size = htonl(
		    sizeof(struct qla2xxx_mqueue_chain) +
		    sizeof(struct qla2xxx_mqueue_header) +
		    (req->length * sizeof(request_t)));
		ptr += sizeof(struct qla2xxx_mqueue_chain);

		/* Add header. */
		qh = ptr;
		qh->queue = htonl(TYPE_REQUEST_QUEUE);
		qh->number = htonl(que);
		qh->size = htonl(req->length * sizeof(request_t));
		ptr += sizeof(struct qla2xxx_mqueue_header);

		/* Add data. */
		memcpy(ptr, req->ring, req->length * sizeof(request_t));
		ptr += req->length * sizeof(request_t);
	}

	/* Response queues */
	for (que = 1; que < ha->max_rsp_queues; que++) {
		rsp = ha->rsp_q_map[que];
		if (!rsp)
			break;

		/* Add chain. */
		q = ptr;
		*last_chain = &q->type;
		q->type = htonl(DUMP_CHAIN_QUEUE);
		q->chain_size = htonl(
		    sizeof(struct qla2xxx_mqueue_chain) +
		    sizeof(struct qla2xxx_mqueue_header) +
		    (rsp->length * sizeof(response_t)));
		ptr += sizeof(struct qla2xxx_mqueue_chain);

		/* Add header. */
		qh = ptr;
		qh->queue = htonl(TYPE_RESPONSE_QUEUE);
		qh->number = htonl(que);
		qh->size = htonl(rsp->length * sizeof(response_t));
		ptr += sizeof(struct qla2xxx_mqueue_header);

		/* Add data. */
		memcpy(ptr, rsp->ring, rsp->length * sizeof(response_t));
		ptr += rsp->length * sizeof(response_t);
	}

	return ptr;
}