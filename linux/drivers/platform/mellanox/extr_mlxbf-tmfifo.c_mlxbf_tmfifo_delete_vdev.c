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
struct mlxbf_tmfifo_vdev {int /*<<< orphan*/  vdev; } ;
struct mlxbf_tmfifo {int /*<<< orphan*/  lock; struct mlxbf_tmfifo_vdev** vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxbf_tmfifo_free_vrings (struct mlxbf_tmfifo*,struct mlxbf_tmfifo_vdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_virtio_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxbf_tmfifo_delete_vdev(struct mlxbf_tmfifo *fifo, int vdev_id)
{
	struct mlxbf_tmfifo_vdev *tm_vdev;

	mutex_lock(&fifo->lock);

	/* Unregister vdev. */
	tm_vdev = fifo->vdev[vdev_id];
	if (tm_vdev) {
		unregister_virtio_device(&tm_vdev->vdev);
		mlxbf_tmfifo_free_vrings(fifo, tm_vdev);
		fifo->vdev[vdev_id] = NULL;
	}

	mutex_unlock(&fifo->lock);

	return 0;
}