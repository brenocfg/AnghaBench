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
typedef  scalar_t__ u32 ;
struct nvkm_msgqueue_queue {scalar_t__ offset; scalar_t__ size; int /*<<< orphan*/  tail_reg; int /*<<< orphan*/  head_reg; } ;
struct nvkm_msgqueue {struct nvkm_falcon* falcon; } ;
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HDR_SIZE ; 
 int /*<<< orphan*/  QUEUE_ALIGNMENT ; 
 scalar_t__ nvkm_falcon_rd32 (struct nvkm_falcon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
cmd_queue_has_room(struct nvkm_msgqueue *priv, struct nvkm_msgqueue_queue *queue,
		   u32 size, bool *rewind)
{
	struct nvkm_falcon *falcon = priv->falcon;
	u32 head, tail, free;

	size = ALIGN(size, QUEUE_ALIGNMENT);

	head = nvkm_falcon_rd32(falcon, queue->head_reg);
	tail = nvkm_falcon_rd32(falcon, queue->tail_reg);

	if (head >= tail) {
		free = queue->offset + queue->size - head;
		free -= HDR_SIZE;

		if (size > free) {
			*rewind = true;
			head = queue->offset;
		}
	}

	if (head < tail)
		free = tail - head - 1;

	return size <= free;
}