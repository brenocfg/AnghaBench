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
typedef  int u32 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_msgqueue_queue {int index; } ;
struct nvkm_msgqueue_hdr {int size; } ;
struct nvkm_msgqueue {TYPE_1__* falcon; } ;
struct TYPE_2__ {struct nvkm_subdev* owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int HDR_SIZE ; 
 int MSG_BUF_SIZE ; 
 int /*<<< orphan*/  msg_queue_close (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*,int) ; 
 scalar_t__ msg_queue_empty (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*) ; 
 int msg_queue_open (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*) ; 
 int msg_queue_pop (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*,struct nvkm_msgqueue_hdr*,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev const*,char*,int) ; 

__attribute__((used)) static int
msg_queue_read(struct nvkm_msgqueue *priv, struct nvkm_msgqueue_queue *queue,
	       struct nvkm_msgqueue_hdr *hdr)
{
	const struct nvkm_subdev *subdev = priv->falcon->owner;
	int err;

	err = msg_queue_open(priv, queue);
	if (err) {
		nvkm_error(subdev, "fail to open queue %d\n", queue->index);
		return err;
	}

	if (msg_queue_empty(priv, queue)) {
		err = 0;
		goto close;
	}

	err = msg_queue_pop(priv, queue, hdr, HDR_SIZE);
	if (err >= 0 && err != HDR_SIZE)
		err = -EINVAL;
	if (err < 0) {
		nvkm_error(subdev, "failed to read message header: %d\n", err);
		goto close;
	}

	if (hdr->size > MSG_BUF_SIZE) {
		nvkm_error(subdev, "message too big (%d bytes)\n", hdr->size);
		err = -ENOSPC;
		goto close;
	}

	if (hdr->size > HDR_SIZE) {
		u32 read_size = hdr->size - HDR_SIZE;

		err = msg_queue_pop(priv, queue, (hdr + 1), read_size);
		if (err >= 0 && err != read_size)
			err = -EINVAL;
		if (err < 0) {
			nvkm_error(subdev, "failed to read message: %d\n", err);
			goto close;
		}
	}

close:
	msg_queue_close(priv, queue, (err >= 0));

	return err;
}