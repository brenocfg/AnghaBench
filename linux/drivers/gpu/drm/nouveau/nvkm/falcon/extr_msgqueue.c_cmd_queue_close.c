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
struct nvkm_msgqueue_queue {int /*<<< orphan*/  mutex; int /*<<< orphan*/  position; int /*<<< orphan*/  head_reg; } ;
struct nvkm_msgqueue {struct nvkm_falcon* falcon; } ;
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cmd_queue_close(struct nvkm_msgqueue *priv, struct nvkm_msgqueue_queue *queue,
		bool commit)
{
	struct nvkm_falcon *falcon = priv->falcon;

	if (commit)
		nvkm_falcon_wr32(falcon, queue->head_reg, queue->position);

	mutex_unlock(&queue->mutex);
}