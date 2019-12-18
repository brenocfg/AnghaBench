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
struct virtio_mmio_device {int /*<<< orphan*/  pdev; } ;
struct virtio_device {int /*<<< orphan*/  dev; } ;
struct irq_affinity {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct virtqueue*) ; 
 int PTR_ERR (struct virtqueue*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int platform_get_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtio_mmio_device*) ; 
 struct virtio_mmio_device* to_virtio_mmio_device (struct virtio_device*) ; 
 int /*<<< orphan*/  vm_del_vqs (struct virtio_device*) ; 
 int /*<<< orphan*/  vm_interrupt ; 
 struct virtqueue* vm_setup_vq (struct virtio_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const* const,int const) ; 

__attribute__((used)) static int vm_find_vqs(struct virtio_device *vdev, unsigned nvqs,
		       struct virtqueue *vqs[],
		       vq_callback_t *callbacks[],
		       const char * const names[],
		       const bool *ctx,
		       struct irq_affinity *desc)
{
	struct virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);
	int irq = platform_get_irq(vm_dev->pdev, 0);
	int i, err, queue_idx = 0;

	if (irq < 0) {
		dev_err(&vdev->dev, "Cannot get IRQ resource\n");
		return irq;
	}

	err = request_irq(irq, vm_interrupt, IRQF_SHARED,
			dev_name(&vdev->dev), vm_dev);
	if (err)
		return err;

	for (i = 0; i < nvqs; ++i) {
		if (!names[i]) {
			vqs[i] = NULL;
			continue;
		}

		vqs[i] = vm_setup_vq(vdev, queue_idx++, callbacks[i], names[i],
				     ctx ? ctx[i] : false);
		if (IS_ERR(vqs[i])) {
			vm_del_vqs(vdev);
			return PTR_ERR(vqs[i]);
		}
	}

	return 0;
}