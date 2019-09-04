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
struct vb2_threadio_data {int stop; int /*<<< orphan*/ * thread; } ;
struct vb2_queue {struct vb2_threadio_data* threadio; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vb2_cleanup_fileio (struct vb2_queue*) ; 
 int /*<<< orphan*/  kfree (struct vb2_threadio_data*) ; 
 int kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_queue_error (struct vb2_queue*) ; 

int vb2_thread_stop(struct vb2_queue *q)
{
	struct vb2_threadio_data *threadio = q->threadio;
	int err;

	if (threadio == NULL)
		return 0;
	threadio->stop = true;
	/* Wake up all pending sleeps in the thread */
	vb2_queue_error(q);
	err = kthread_stop(threadio->thread);
	__vb2_cleanup_fileio(q);
	threadio->thread = NULL;
	kfree(threadio);
	q->threadio = NULL;
	return err;
}