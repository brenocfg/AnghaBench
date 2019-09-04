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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_msgqueue_queue {int /*<<< orphan*/  head_reg; int /*<<< orphan*/  position; int /*<<< orphan*/  mutex; } ;
struct nvkm_msgqueue {struct nvkm_falcon* falcon; } ;
struct nvkm_falcon {struct nvkm_subdev* owner; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  cmd_queue_has_room (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cmd_queue_rewind (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev const*,char*) ; 
 int /*<<< orphan*/  nvkm_falcon_rd32 (struct nvkm_falcon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmd_queue_open(struct nvkm_msgqueue *priv, struct nvkm_msgqueue_queue *queue,
	       u32 size)
{
	struct nvkm_falcon *falcon = priv->falcon;
	const struct nvkm_subdev *subdev = priv->falcon->owner;
	bool rewind = false;

	mutex_lock(&queue->mutex);

	if (!cmd_queue_has_room(priv, queue, size, &rewind)) {
		nvkm_error(subdev, "queue full\n");
		mutex_unlock(&queue->mutex);
		return -EAGAIN;
	}

	queue->position = nvkm_falcon_rd32(falcon, queue->head_reg);

	if (rewind)
		cmd_queue_rewind(priv, queue);

	return 0;
}