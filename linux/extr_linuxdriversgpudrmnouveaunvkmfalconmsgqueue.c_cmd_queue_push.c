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
struct nvkm_msgqueue_queue {int /*<<< orphan*/  position; } ;
struct nvkm_msgqueue {int /*<<< orphan*/  falcon; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_ALIGNMENT ; 
 int /*<<< orphan*/  nvkm_falcon_load_dmem (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmd_queue_push(struct nvkm_msgqueue *priv, struct nvkm_msgqueue_queue *queue,
	       void *data, u32 size)
{
	nvkm_falcon_load_dmem(priv->falcon, data, queue->position, size, 0);
	queue->position += ALIGN(size, QUEUE_ALIGNMENT);

	return 0;
}