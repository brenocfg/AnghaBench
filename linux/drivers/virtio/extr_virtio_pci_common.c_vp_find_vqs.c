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
typedef  int /*<<< orphan*/  vq_callback_t ;
struct virtqueue {int dummy; } ;
struct virtio_device {int dummy; } ;
struct irq_affinity {int dummy; } ;

/* Variables and functions */
 int vp_find_vqs_intx (struct virtio_device*,unsigned int,struct virtqueue**,int /*<<< orphan*/ **,char const* const*,int const*) ; 
 int vp_find_vqs_msix (struct virtio_device*,unsigned int,struct virtqueue**,int /*<<< orphan*/ **,char const* const*,int,int const*,struct irq_affinity*) ; 

int vp_find_vqs(struct virtio_device *vdev, unsigned nvqs,
		struct virtqueue *vqs[], vq_callback_t *callbacks[],
		const char * const names[], const bool *ctx,
		struct irq_affinity *desc)
{
	int err;

	/* Try MSI-X with one vector per queue. */
	err = vp_find_vqs_msix(vdev, nvqs, vqs, callbacks, names, true, ctx, desc);
	if (!err)
		return 0;
	/* Fallback: MSI-X with one vector for config, one shared for queues. */
	err = vp_find_vqs_msix(vdev, nvqs, vqs, callbacks, names, false, ctx, desc);
	if (!err)
		return 0;
	/* Finally fall back to regular interrupts. */
	return vp_find_vqs_intx(vdev, nvqs, vqs, callbacks, names, ctx);
}