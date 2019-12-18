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
struct vring_desc {int dummy; } ;
struct mlxbf_tmfifo_vring {scalar_t__ vdev_id; struct vring_desc* desc; struct vring_desc* desc_head; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_ID_NET ; 
 struct vring_desc* mlxbf_tmfifo_get_next_desc (struct mlxbf_tmfifo_vring*) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_init_net_desc (struct mlxbf_tmfifo_vring*,struct vring_desc*,int) ; 

__attribute__((used)) static struct vring_desc *
mlxbf_tmfifo_get_next_pkt(struct mlxbf_tmfifo_vring *vring, bool is_rx)
{
	struct vring_desc *desc;

	desc = mlxbf_tmfifo_get_next_desc(vring);
	if (desc && is_rx && vring->vdev_id == VIRTIO_ID_NET)
		mlxbf_tmfifo_init_net_desc(vring, desc, is_rx);

	vring->desc_head = desc;
	vring->desc = desc;

	return desc;
}