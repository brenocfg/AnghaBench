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
struct vring {int dummy; } ;
struct virtqueue {int dummy; } ;
struct virtio_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_F_RING_PACKED ; 
 struct virtqueue* __vring_new_virtqueue (unsigned int,struct vring,struct virtio_device*,int,int,int (*) (struct virtqueue*),void (*) (struct virtqueue*),char const*) ; 
 scalar_t__ virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_init (struct vring*,unsigned int,void*,unsigned int) ; 

struct virtqueue *vring_new_virtqueue(unsigned int index,
				      unsigned int num,
				      unsigned int vring_align,
				      struct virtio_device *vdev,
				      bool weak_barriers,
				      bool context,
				      void *pages,
				      bool (*notify)(struct virtqueue *vq),
				      void (*callback)(struct virtqueue *vq),
				      const char *name)
{
	struct vring vring;

	if (virtio_has_feature(vdev, VIRTIO_F_RING_PACKED))
		return NULL;

	vring_init(&vring, num, pages, vring_align);
	return __vring_new_virtqueue(index, vring, vdev, weak_barriers, context,
				     notify, callback, name);
}