#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct page {int dummy; } ;
struct TYPE_6__ {scalar_t__ sqhd_disabled; } ;
struct nvmet_tcp_queue {TYPE_1__ nvme_sq; int /*<<< orphan*/ * snd_cmd; scalar_t__ data_digest; int /*<<< orphan*/  sock; } ;
struct TYPE_7__ {int /*<<< orphan*/  sg; } ;
struct nvmet_tcp_cmd {int offset; int wbytes_done; TYPE_2__ req; int /*<<< orphan*/  iov; struct nvmet_tcp_queue* queue; int /*<<< orphan*/  state; TYPE_3__* cur_sg; } ;
struct TYPE_8__ {int length; } ;

/* Variables and functions */
 int MSG_DONTWAIT ; 
 int MSG_MORE ; 
 int /*<<< orphan*/  NVMET_TCP_SEND_DDGST ; 
 int kernel_sendpage (int /*<<< orphan*/ ,struct page*,int,int,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_setup_response_pdu (struct nvmet_tcp_cmd*) ; 
 int /*<<< orphan*/  nvmet_tcp_put_cmd (struct nvmet_tcp_cmd*) ; 
 TYPE_3__* sg_next (TYPE_3__*) ; 
 struct page* sg_page (TYPE_3__*) ; 
 int /*<<< orphan*/  sgl_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvmet_try_send_data(struct nvmet_tcp_cmd *cmd)
{
	struct nvmet_tcp_queue *queue = cmd->queue;
	int ret;

	while (cmd->cur_sg) {
		struct page *page = sg_page(cmd->cur_sg);
		u32 left = cmd->cur_sg->length - cmd->offset;

		ret = kernel_sendpage(cmd->queue->sock, page, cmd->offset,
					left, MSG_DONTWAIT | MSG_MORE);
		if (ret <= 0)
			return ret;

		cmd->offset += ret;
		cmd->wbytes_done += ret;

		/* Done with sg?*/
		if (cmd->offset == cmd->cur_sg->length) {
			cmd->cur_sg = sg_next(cmd->cur_sg);
			cmd->offset = 0;
		}
	}

	if (queue->data_digest) {
		cmd->state = NVMET_TCP_SEND_DDGST;
		cmd->offset = 0;
	} else {
		if (queue->nvme_sq.sqhd_disabled) {
			cmd->queue->snd_cmd = NULL;
			nvmet_tcp_put_cmd(cmd);
		} else {
			nvmet_setup_response_pdu(cmd);
		}
	}

	if (queue->nvme_sq.sqhd_disabled) {
		kfree(cmd->iov);
		sgl_free(cmd->req.sg);
	}

	return 1;

}