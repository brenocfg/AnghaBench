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
struct vector_queue {int tail; int max_depth; int queue_depth; int /*<<< orphan*/  head_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vector_advancetail(struct vector_queue *qi, int advance)
{
	int queue_depth;

	qi->tail =
		(qi->tail + advance)
			% qi->max_depth;
	spin_lock(&qi->head_lock);
	qi->queue_depth += advance;
	queue_depth = qi->queue_depth;
	spin_unlock(&qi->head_lock);
	return queue_depth;
}