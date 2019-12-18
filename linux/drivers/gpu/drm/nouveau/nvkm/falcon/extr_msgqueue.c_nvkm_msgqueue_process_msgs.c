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
typedef  int /*<<< orphan*/  u8 ;
struct nvkm_msgqueue_queue {int dummy; } ;
struct nvkm_msgqueue_hdr {int dummy; } ;
struct nvkm_msgqueue {int init_msg_received; } ;

/* Variables and functions */
 int MSG_BUF_SIZE ; 
 scalar_t__ msg_queue_read (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*,struct nvkm_msgqueue_hdr*) ; 
 int msgqueue_handle_init_msg (struct nvkm_msgqueue*,struct nvkm_msgqueue_hdr*) ; 
 int /*<<< orphan*/  msgqueue_msg_handle (struct nvkm_msgqueue*,struct nvkm_msgqueue_hdr*) ; 

void
nvkm_msgqueue_process_msgs(struct nvkm_msgqueue *priv,
			   struct nvkm_msgqueue_queue *queue)
{
	/*
	 * We are invoked from a worker thread, so normally we have plenty of
	 * stack space to work with.
	 */
	u8 msg_buffer[MSG_BUF_SIZE];
	struct nvkm_msgqueue_hdr *hdr = (void *)msg_buffer;
	int ret;

	/* the first message we receive must be the init message */
	if ((!priv->init_msg_received)) {
		ret = msgqueue_handle_init_msg(priv, hdr);
		if (!ret)
			priv->init_msg_received = true;
	} else {
		while (msg_queue_read(priv, queue, hdr) > 0)
			msgqueue_msg_handle(priv, hdr);
	}
}