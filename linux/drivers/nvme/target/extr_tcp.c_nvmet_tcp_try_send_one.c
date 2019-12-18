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
struct nvmet_tcp_queue {scalar_t__ state; struct nvmet_tcp_cmd* snd_cmd; } ;
struct nvmet_tcp_cmd {scalar_t__ state; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ NVMET_TCP_Q_DISCONNECTING ; 
 scalar_t__ NVMET_TCP_SEND_DATA ; 
 scalar_t__ NVMET_TCP_SEND_DATA_PDU ; 
 scalar_t__ NVMET_TCP_SEND_DDGST ; 
 scalar_t__ NVMET_TCP_SEND_R2T ; 
 scalar_t__ NVMET_TCP_SEND_RESPONSE ; 
 struct nvmet_tcp_cmd* nvmet_tcp_fetch_cmd (struct nvmet_tcp_queue*) ; 
 int nvmet_try_send_data (struct nvmet_tcp_cmd*) ; 
 int nvmet_try_send_data_pdu (struct nvmet_tcp_cmd*) ; 
 int nvmet_try_send_ddgst (struct nvmet_tcp_cmd*) ; 
 int nvmet_try_send_r2t (struct nvmet_tcp_cmd*,int) ; 
 int nvmet_try_send_response (struct nvmet_tcp_cmd*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvmet_tcp_try_send_one(struct nvmet_tcp_queue *queue,
		bool last_in_batch)
{
	struct nvmet_tcp_cmd *cmd = queue->snd_cmd;
	int ret = 0;

	if (!cmd || queue->state == NVMET_TCP_Q_DISCONNECTING) {
		cmd = nvmet_tcp_fetch_cmd(queue);
		if (unlikely(!cmd))
			return 0;
	}

	if (cmd->state == NVMET_TCP_SEND_DATA_PDU) {
		ret = nvmet_try_send_data_pdu(cmd);
		if (ret <= 0)
			goto done_send;
	}

	if (cmd->state == NVMET_TCP_SEND_DATA) {
		ret = nvmet_try_send_data(cmd);
		if (ret <= 0)
			goto done_send;
	}

	if (cmd->state == NVMET_TCP_SEND_DDGST) {
		ret = nvmet_try_send_ddgst(cmd);
		if (ret <= 0)
			goto done_send;
	}

	if (cmd->state == NVMET_TCP_SEND_R2T) {
		ret = nvmet_try_send_r2t(cmd, last_in_batch);
		if (ret <= 0)
			goto done_send;
	}

	if (cmd->state == NVMET_TCP_SEND_RESPONSE)
		ret = nvmet_try_send_response(cmd, last_in_batch);

done_send:
	if (ret < 0) {
		if (ret == -EAGAIN)
			return 0;
		return ret;
	}

	return 1;
}