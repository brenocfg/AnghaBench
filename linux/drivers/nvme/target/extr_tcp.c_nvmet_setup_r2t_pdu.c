#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct nvmet_tcp_queue {int /*<<< orphan*/  snd_hash; scalar_t__ hdr_digest; } ;
struct TYPE_7__ {scalar_t__ transfer_len; TYPE_2__* cmd; } ;
struct nvmet_tcp_cmd {struct nvmet_tcp_queue* queue; scalar_t__ rbytes_done; TYPE_3__ req; int /*<<< orphan*/  state; scalar_t__ offset; struct nvme_tcp_r2t_pdu* r2t_pdu; } ;
struct TYPE_8__ {int hlen; int /*<<< orphan*/  flags; void* plen; scalar_t__ pdo; int /*<<< orphan*/  type; } ;
struct nvme_tcp_r2t_pdu {TYPE_4__ hdr; void* r2t_offset; void* r2t_length; int /*<<< orphan*/  ttag; int /*<<< orphan*/  command_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  command_id; } ;
struct TYPE_6__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMET_TCP_SEND_R2T ; 
 int /*<<< orphan*/  NVME_TCP_F_HDGST ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  nvme_tcp_r2t ; 
 int /*<<< orphan*/  nvmet_tcp_cmd_tag (struct nvmet_tcp_queue*,struct nvmet_tcp_cmd*) ; 
 int /*<<< orphan*/  nvmet_tcp_hdgst (int /*<<< orphan*/ ,struct nvme_tcp_r2t_pdu*,int) ; 
 scalar_t__ nvmet_tcp_hdgst_len (struct nvmet_tcp_queue*) ; 

__attribute__((used)) static void nvmet_setup_r2t_pdu(struct nvmet_tcp_cmd *cmd)
{
	struct nvme_tcp_r2t_pdu *pdu = cmd->r2t_pdu;
	struct nvmet_tcp_queue *queue = cmd->queue;
	u8 hdgst = nvmet_tcp_hdgst_len(cmd->queue);

	cmd->offset = 0;
	cmd->state = NVMET_TCP_SEND_R2T;

	pdu->hdr.type = nvme_tcp_r2t;
	pdu->hdr.flags = 0;
	pdu->hdr.hlen = sizeof(*pdu);
	pdu->hdr.pdo = 0;
	pdu->hdr.plen = cpu_to_le32(pdu->hdr.hlen + hdgst);

	pdu->command_id = cmd->req.cmd->common.command_id;
	pdu->ttag = nvmet_tcp_cmd_tag(cmd->queue, cmd);
	pdu->r2t_length = cpu_to_le32(cmd->req.transfer_len - cmd->rbytes_done);
	pdu->r2t_offset = cpu_to_le32(cmd->rbytes_done);
	if (cmd->queue->hdr_digest) {
		pdu->hdr.flags |= NVME_TCP_F_HDGST;
		nvmet_tcp_hdgst(queue->snd_hash, pdu, sizeof(*pdu));
	}
}