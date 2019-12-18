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
struct nvmet_tcp_queue {scalar_t__ rcv_state; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ NVMET_TCP_RECV_DATA ; 
 scalar_t__ NVMET_TCP_RECV_DDGST ; 
 scalar_t__ NVMET_TCP_RECV_ERR ; 
 scalar_t__ NVMET_TCP_RECV_PDU ; 
 int nvmet_tcp_try_recv_data (struct nvmet_tcp_queue*) ; 
 int nvmet_tcp_try_recv_ddgst (struct nvmet_tcp_queue*) ; 
 int nvmet_tcp_try_recv_pdu (struct nvmet_tcp_queue*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvmet_tcp_try_recv_one(struct nvmet_tcp_queue *queue)
{
	int result = 0;

	if (unlikely(queue->rcv_state == NVMET_TCP_RECV_ERR))
		return 0;

	if (queue->rcv_state == NVMET_TCP_RECV_PDU) {
		result = nvmet_tcp_try_recv_pdu(queue);
		if (result != 0)
			goto done_recv;
	}

	if (queue->rcv_state == NVMET_TCP_RECV_DATA) {
		result = nvmet_tcp_try_recv_data(queue);
		if (result != 0)
			goto done_recv;
	}

	if (queue->rcv_state == NVMET_TCP_RECV_DDGST) {
		result = nvmet_tcp_try_recv_ddgst(queue);
		if (result != 0)
			goto done_recv;
	}

done_recv:
	if (result < 0) {
		if (result == -EAGAIN)
			return 0;
		return result;
	}
	return 1;
}