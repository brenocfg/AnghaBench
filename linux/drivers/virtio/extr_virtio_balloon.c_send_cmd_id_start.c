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
struct virtqueue {int dummy; } ;
struct virtio_balloon {int /*<<< orphan*/  cmd_id_active; int /*<<< orphan*/  vdev; struct virtqueue* free_page_vq; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  virtio32_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_balloon_cmd_id_received (struct virtio_balloon*) ; 
 int virtqueue_add_outbuf (struct virtqueue*,struct scatterlist*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ virtqueue_get_buf (struct virtqueue*,int*) ; 
 int /*<<< orphan*/  virtqueue_kick (struct virtqueue*) ; 

__attribute__((used)) static int send_cmd_id_start(struct virtio_balloon *vb)
{
	struct scatterlist sg;
	struct virtqueue *vq = vb->free_page_vq;
	int err, unused;

	/* Detach all the used buffers from the vq */
	while (virtqueue_get_buf(vq, &unused))
		;

	vb->cmd_id_active = virtio32_to_cpu(vb->vdev,
					virtio_balloon_cmd_id_received(vb));
	sg_init_one(&sg, &vb->cmd_id_active, sizeof(vb->cmd_id_active));
	err = virtqueue_add_outbuf(vq, &sg, 1, &vb->cmd_id_active, GFP_KERNEL);
	if (!err)
		virtqueue_kick(vq);
	return err;
}