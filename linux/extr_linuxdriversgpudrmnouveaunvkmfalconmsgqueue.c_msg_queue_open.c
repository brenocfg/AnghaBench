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
struct nvkm_msgqueue_queue {int /*<<< orphan*/  tail_reg; int /*<<< orphan*/  position; int /*<<< orphan*/  mutex; } ;
struct nvkm_msgqueue {struct nvkm_falcon* falcon; } ;
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_falcon_rd32 (struct nvkm_falcon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msg_queue_open(struct nvkm_msgqueue *priv, struct nvkm_msgqueue_queue *queue)
{
	struct nvkm_falcon *falcon = priv->falcon;

	mutex_lock(&queue->mutex);

	queue->position = nvkm_falcon_rd32(falcon, queue->tail_reg);

	return 0;
}