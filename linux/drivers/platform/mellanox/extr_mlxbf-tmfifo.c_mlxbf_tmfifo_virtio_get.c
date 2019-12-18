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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct virtio_device {int dummy; } ;
struct mlxbf_tmfifo_vdev {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,unsigned int) ; 
 struct mlxbf_tmfifo_vdev* mlxbf_vdev_to_tmfifo (struct virtio_device*) ; 

__attribute__((used)) static void mlxbf_tmfifo_virtio_get(struct virtio_device *vdev,
				    unsigned int offset,
				    void *buf,
				    unsigned int len)
{
	struct mlxbf_tmfifo_vdev *tm_vdev = mlxbf_vdev_to_tmfifo(vdev);

	if ((u64)offset + len > sizeof(tm_vdev->config))
		return;

	memcpy(buf, (u8 *)&tm_vdev->config + offset, len);
}