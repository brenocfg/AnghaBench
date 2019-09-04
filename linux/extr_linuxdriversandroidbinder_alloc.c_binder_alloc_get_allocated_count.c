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
struct rb_node {int dummy; } ;
struct binder_alloc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  allocated_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_first (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 

int binder_alloc_get_allocated_count(struct binder_alloc *alloc)
{
	struct rb_node *n;
	int count = 0;

	mutex_lock(&alloc->mutex);
	for (n = rb_first(&alloc->allocated_buffers); n != NULL; n = rb_next(n))
		count++;
	mutex_unlock(&alloc->mutex);
	return count;
}