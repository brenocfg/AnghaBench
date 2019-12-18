#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_5__ {TYPE_1__* used; } ;
struct TYPE_6__ {TYPE_2__ vring; } ;
struct vring_virtqueue {TYPE_3__ split; } ;
struct virtqueue {int /*<<< orphan*/  vdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 
 scalar_t__ virtio16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool virtqueue_poll_split(struct virtqueue *_vq, unsigned last_used_idx)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	return (u16)last_used_idx != virtio16_to_cpu(_vq->vdev,
			vq->split.vring.used->idx);
}