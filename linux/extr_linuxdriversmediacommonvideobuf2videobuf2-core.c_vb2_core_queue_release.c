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
struct vb2_queue {int /*<<< orphan*/  mmap_lock; int /*<<< orphan*/  num_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vb2_cleanup_fileio (struct vb2_queue*) ; 
 int /*<<< orphan*/  __vb2_queue_cancel (struct vb2_queue*) ; 
 int /*<<< orphan*/  __vb2_queue_free (struct vb2_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void vb2_core_queue_release(struct vb2_queue *q)
{
	__vb2_cleanup_fileio(q);
	__vb2_queue_cancel(q);
	mutex_lock(&q->mmap_lock);
	__vb2_queue_free(q, q->num_buffers);
	mutex_unlock(&q->mmap_lock);
}