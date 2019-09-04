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
struct vector_queue {int head; int max_depth; int queue_depth; int /*<<< orphan*/  tail_lock; scalar_t__ tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vector_advancehead(struct vector_queue *qi, int advance)
{
	int queue_depth;

	qi->head =
		(qi->head + advance)
			% qi->max_depth;


	spin_lock(&qi->tail_lock);
	qi->queue_depth -= advance;

	/* we are at 0, use this to
	 * reset head and tail so we can use max size vectors
	 */

	if (qi->queue_depth == 0) {
		qi->head = 0;
		qi->tail = 0;
	}
	queue_depth = qi->queue_depth;
	spin_unlock(&qi->tail_lock);
	return queue_depth;
}