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
struct vchiu_queue {int size; int initialized; int /*<<< orphan*/  storage; int /*<<< orphan*/  push; int /*<<< orphan*/  pop; scalar_t__ write; scalar_t__ read; } ;
struct vchiq_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_pow2 (int) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiu_queue_delete (struct vchiu_queue*) ; 

int vchiu_queue_init(struct vchiu_queue *queue, int size)
{
	WARN_ON(!is_pow2(size));

	queue->size = size;
	queue->read = 0;
	queue->write = 0;
	queue->initialized = 1;

	init_completion(&queue->pop);
	init_completion(&queue->push);

	queue->storage = kcalloc(size, sizeof(struct vchiq_header *),
				 GFP_KERNEL);
	if (!queue->storage) {
		vchiu_queue_delete(queue);
		return 0;
	}
	return 1;
}