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
struct nvkm_msgqueue_queue {int dummy; } ;
struct nvkm_msgqueue {int dummy; } ;
struct msgqueue_0137c63d {int /*<<< orphan*/  base; struct nvkm_msgqueue_queue* queue; } ;

/* Variables and functions */
 size_t MSGQUEUE_0137C63D_MESSAGE_QUEUE ; 
 struct msgqueue_0137c63d* msgqueue_0137c63d (struct nvkm_msgqueue*) ; 
 int /*<<< orphan*/  nvkm_msgqueue_process_msgs (int /*<<< orphan*/ *,struct nvkm_msgqueue_queue*) ; 

__attribute__((used)) static void
msgqueue_0137c63d_process_msgs(struct nvkm_msgqueue *queue)
{
	struct msgqueue_0137c63d *priv = msgqueue_0137c63d(queue);
	struct nvkm_msgqueue_queue *q_queue =
		&priv->queue[MSGQUEUE_0137C63D_MESSAGE_QUEUE];

	nvkm_msgqueue_process_msgs(&priv->base, q_queue);
}