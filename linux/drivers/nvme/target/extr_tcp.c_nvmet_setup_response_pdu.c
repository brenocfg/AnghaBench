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
typedef  scalar_t__ u8 ;
struct nvmet_tcp_queue {int /*<<< orphan*/  snd_hash; scalar_t__ hdr_digest; } ;
struct nvmet_tcp_cmd {struct nvmet_tcp_queue* queue; int /*<<< orphan*/  state; scalar_t__ offset; struct nvme_tcp_rsp_pdu* rsp_pdu; } ;
struct TYPE_2__ {int hlen; int /*<<< orphan*/  flags; int /*<<< orphan*/  plen; scalar_t__ pdo; int /*<<< orphan*/  type; } ;
struct nvme_tcp_rsp_pdu {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMET_TCP_SEND_RESPONSE ; 
 int /*<<< orphan*/  NVME_TCP_F_HDGST ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  nvme_tcp_rsp ; 
 int /*<<< orphan*/  nvmet_tcp_hdgst (int /*<<< orphan*/ ,struct nvme_tcp_rsp_pdu*,int) ; 
 scalar_t__ nvmet_tcp_hdgst_len (struct nvmet_tcp_queue*) ; 

__attribute__((used)) static void nvmet_setup_response_pdu(struct nvmet_tcp_cmd *cmd)
{
	struct nvme_tcp_rsp_pdu *pdu = cmd->rsp_pdu;
	struct nvmet_tcp_queue *queue = cmd->queue;
	u8 hdgst = nvmet_tcp_hdgst_len(cmd->queue);

	cmd->offset = 0;
	cmd->state = NVMET_TCP_SEND_RESPONSE;

	pdu->hdr.type = nvme_tcp_rsp;
	pdu->hdr.flags = 0;
	pdu->hdr.hlen = sizeof(*pdu);
	pdu->hdr.pdo = 0;
	pdu->hdr.plen = cpu_to_le32(pdu->hdr.hlen + hdgst);
	if (cmd->queue->hdr_digest) {
		pdu->hdr.flags |= NVME_TCP_F_HDGST;
		nvmet_tcp_hdgst(queue->snd_hash, pdu, sizeof(*pdu));
	}
}