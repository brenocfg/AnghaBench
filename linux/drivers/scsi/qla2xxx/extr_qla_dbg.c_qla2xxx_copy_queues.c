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
struct rsp_que {int length; int /*<<< orphan*/  ring; } ;
struct req_que {int length; int /*<<< orphan*/  ring; } ;
struct qla_hw_data {struct rsp_que** rsp_q_map; struct req_que** req_q_map; } ;
typedef  int /*<<< orphan*/  response_t ;
typedef  int /*<<< orphan*/  request_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void *
qla2xxx_copy_queues(struct qla_hw_data *ha, void *ptr)
{
	struct req_que *req = ha->req_q_map[0];
	struct rsp_que *rsp = ha->rsp_q_map[0];
	/* Request queue. */
	memcpy(ptr, req->ring, req->length *
	    sizeof(request_t));

	/* Response queue. */
	ptr += req->length * sizeof(request_t);
	memcpy(ptr, rsp->ring, rsp->length  *
	    sizeof(response_t));

	return ptr + (rsp->length * sizeof(response_t));
}