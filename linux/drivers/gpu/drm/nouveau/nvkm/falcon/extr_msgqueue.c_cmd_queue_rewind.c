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
struct nvkm_subdev {int dummy; } ;
struct nvkm_msgqueue_queue {int /*<<< orphan*/  offset; int /*<<< orphan*/  position; int /*<<< orphan*/  index; } ;
struct nvkm_msgqueue_hdr {int size; int /*<<< orphan*/  unit_id; } ;
struct nvkm_msgqueue {TYPE_1__* falcon; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {struct nvkm_subdev* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGQUEUE_UNIT_REWIND ; 
 int cmd_queue_push (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*,struct nvkm_msgqueue_hdr*,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cmd_queue_rewind(struct nvkm_msgqueue *priv, struct nvkm_msgqueue_queue *queue)
{
	const struct nvkm_subdev *subdev = priv->falcon->owner;
	struct nvkm_msgqueue_hdr cmd;
	int err;

	cmd.unit_id = MSGQUEUE_UNIT_REWIND;
	cmd.size = sizeof(cmd);
	err = cmd_queue_push(priv, queue, &cmd, cmd.size);
	if (err)
		nvkm_error(subdev, "queue %d rewind failed\n", queue->index);
	else
		nvkm_error(subdev, "queue %d rewinded\n", queue->index);

	queue->position = queue->offset;
}