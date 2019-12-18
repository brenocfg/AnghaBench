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
struct req_que {scalar_t__ ring_index; scalar_t__ length; int /*<<< orphan*/  req_q_in; int /*<<< orphan*/  ring_ptr; int /*<<< orphan*/  ring; } ;
struct qla_qpair {struct req_que* req; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRT_REG_DWORD (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void
qla_83xx_start_iocbs(struct qla_qpair *qpair)
{
	struct req_que *req = qpair->req;

	req->ring_index++;
	if (req->ring_index == req->length) {
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	} else
		req->ring_ptr++;

	WRT_REG_DWORD(req->req_q_in, req->ring_index);
}