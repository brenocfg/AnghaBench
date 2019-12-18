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
struct video_device {struct vb2_queue* queue; struct mutex* lock; } ;
struct vb2_queue {int /*<<< orphan*/  owner; void* fileio; struct mutex* lock; } ;
struct mutex {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLERR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ mutex_lock_interruptible (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  vb2_poll (struct vb2_queue*,struct file*,int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 

__poll_t vb2_fop_poll(struct file *file, poll_table *wait)
{
	struct video_device *vdev = video_devdata(file);
	struct vb2_queue *q = vdev->queue;
	struct mutex *lock = q->lock ? q->lock : vdev->lock;
	__poll_t res;
	void *fileio;

	/*
	 * If this helper doesn't know how to lock, then you shouldn't be using
	 * it but you should write your own.
	 */
	WARN_ON(!lock);

	if (lock && mutex_lock_interruptible(lock))
		return EPOLLERR;

	fileio = q->fileio;

	res = vb2_poll(vdev->queue, file, wait);

	/* If fileio was started, then we have a new queue owner. */
	if (!fileio && q->fileio)
		q->owner = file->private_data;
	if (lock)
		mutex_unlock(lock);
	return res;
}