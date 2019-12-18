#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vring_desc {int /*<<< orphan*/  addr; } ;
struct virtio_net_hdr {int dummy; } ;
struct virtio_device {int dummy; } ;
struct mlxbf_tmfifo_vring {TYPE_1__* vq; } ;
struct TYPE_2__ {struct virtio_device* vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct virtio_net_hdr*,int /*<<< orphan*/ ,int) ; 
 struct virtio_net_hdr* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio64_to_cpu (struct virtio_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxbf_tmfifo_init_net_desc(struct mlxbf_tmfifo_vring *vring,
				       struct vring_desc *desc, bool is_rx)
{
	struct virtio_device *vdev = vring->vq->vdev;
	struct virtio_net_hdr *net_hdr;

	net_hdr = phys_to_virt(virtio64_to_cpu(vdev, desc->addr));
	memset(net_hdr, 0, sizeof(*net_hdr));
}