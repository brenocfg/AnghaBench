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
struct virtio_device {int /*<<< orphan*/  features; } ;
struct mlxbf_tmfifo_vdev {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 struct mlxbf_tmfifo_vdev* mlxbf_vdev_to_tmfifo (struct virtio_device*) ; 

__attribute__((used)) static int mlxbf_tmfifo_virtio_finalize_features(struct virtio_device *vdev)
{
	struct mlxbf_tmfifo_vdev *tm_vdev = mlxbf_vdev_to_tmfifo(vdev);

	tm_vdev->features = vdev->features;

	return 0;
}