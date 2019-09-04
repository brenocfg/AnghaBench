#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {int dummy; } ;
struct nvkm_msgqueue_queue {int dummy; } ;
struct nvkm_msgqueue {int dummy; } ;
struct TYPE_4__ {TYPE_1__* falcon; } ;
struct msgqueue_0137c63d {struct nvkm_msgqueue_queue* queue; TYPE_2__ base; } ;
typedef  enum msgqueue_msg_priority { ____Placeholder_msgqueue_msg_priority } msgqueue_msg_priority ;
struct TYPE_3__ {struct nvkm_subdev* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct nvkm_msgqueue_queue* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t MSGQUEUE_0137C63D_COMMAND_QUEUE_HPQ ; 
 size_t MSGQUEUE_0137C63D_COMMAND_QUEUE_LPQ ; 
#define  MSGQUEUE_MSG_PRIORITY_HIGH 129 
#define  MSGQUEUE_MSG_PRIORITY_LOW 128 
 struct msgqueue_0137c63d* msgqueue_0137c63d (struct nvkm_msgqueue*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev const*,char*) ; 

__attribute__((used)) static struct nvkm_msgqueue_queue *
msgqueue_0137c63d_cmd_queue(struct nvkm_msgqueue *queue,
			    enum msgqueue_msg_priority priority)
{
	struct msgqueue_0137c63d *priv = msgqueue_0137c63d(queue);
	const struct nvkm_subdev *subdev = priv->base.falcon->owner;

	switch (priority) {
	case MSGQUEUE_MSG_PRIORITY_HIGH:
		return &priv->queue[MSGQUEUE_0137C63D_COMMAND_QUEUE_HPQ];
	case MSGQUEUE_MSG_PRIORITY_LOW:
		return &priv->queue[MSGQUEUE_0137C63D_COMMAND_QUEUE_LPQ];
	default:
		nvkm_error(subdev, "invalid command queue!\n");
		return ERR_PTR(-EINVAL);
	}
}