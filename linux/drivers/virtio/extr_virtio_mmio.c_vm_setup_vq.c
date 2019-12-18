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
typedef  int u64 ;
typedef  int u32 ;
struct virtqueue {struct virtio_mmio_vq_info* priv; } ;
struct virtio_mmio_vq_info {int /*<<< orphan*/  node; struct virtqueue* vq; } ;
struct virtio_mmio_device {int version; scalar_t__ base; int /*<<< orphan*/  lock; int /*<<< orphan*/  virtqueues; } ;
struct virtio_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct virtqueue* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_ALIGN ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_AVAIL_HIGH ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_AVAIL_LOW ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_DESC_HIGH ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_DESC_LOW ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_NUM ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_NUM_MAX ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_PFN ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_READY ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_SEL ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_USED_HIGH ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_USED_LOW ; 
 int /*<<< orphan*/  VIRTIO_MMIO_VRING_ALIGN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (struct virtio_mmio_vq_info*) ; 
 struct virtio_mmio_vq_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct virtio_mmio_device* to_virtio_mmio_device (struct virtio_device*) ; 
 int virtqueue_get_avail_addr (struct virtqueue*) ; 
 int virtqueue_get_desc_addr (struct virtqueue*) ; 
 int virtqueue_get_used_addr (struct virtqueue*) ; 
 int virtqueue_get_vring_size (struct virtqueue*) ; 
 int /*<<< orphan*/  vm_notify ; 
 struct virtqueue* vring_create_virtqueue (unsigned int,unsigned int,int /*<<< orphan*/ ,struct virtio_device*,int,int,int,int /*<<< orphan*/ ,void (*) (struct virtqueue*),char const*) ; 
 int /*<<< orphan*/  vring_del_virtqueue (struct virtqueue*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static struct virtqueue *vm_setup_vq(struct virtio_device *vdev, unsigned index,
				  void (*callback)(struct virtqueue *vq),
				  const char *name, bool ctx)
{
	struct virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);
	struct virtio_mmio_vq_info *info;
	struct virtqueue *vq;
	unsigned long flags;
	unsigned int num;
	int err;

	if (!name)
		return NULL;

	/* Select the queue we're interested in */
	writel(index, vm_dev->base + VIRTIO_MMIO_QUEUE_SEL);

	/* Queue shouldn't already be set up. */
	if (readl(vm_dev->base + (vm_dev->version == 1 ?
			VIRTIO_MMIO_QUEUE_PFN : VIRTIO_MMIO_QUEUE_READY))) {
		err = -ENOENT;
		goto error_available;
	}

	/* Allocate and fill out our active queue description */
	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (!info) {
		err = -ENOMEM;
		goto error_kmalloc;
	}

	num = readl(vm_dev->base + VIRTIO_MMIO_QUEUE_NUM_MAX);
	if (num == 0) {
		err = -ENOENT;
		goto error_new_virtqueue;
	}

	/* Create the vring */
	vq = vring_create_virtqueue(index, num, VIRTIO_MMIO_VRING_ALIGN, vdev,
				 true, true, ctx, vm_notify, callback, name);
	if (!vq) {
		err = -ENOMEM;
		goto error_new_virtqueue;
	}

	/* Activate the queue */
	writel(virtqueue_get_vring_size(vq), vm_dev->base + VIRTIO_MMIO_QUEUE_NUM);
	if (vm_dev->version == 1) {
		u64 q_pfn = virtqueue_get_desc_addr(vq) >> PAGE_SHIFT;

		/*
		 * virtio-mmio v1 uses a 32bit QUEUE PFN. If we have something
		 * that doesn't fit in 32bit, fail the setup rather than
		 * pretending to be successful.
		 */
		if (q_pfn >> 32) {
			dev_err(&vdev->dev,
				"platform bug: legacy virtio-mmio must not be used with RAM above 0x%llxGB\n",
				0x1ULL << (32 + PAGE_SHIFT - 30));
			err = -E2BIG;
			goto error_bad_pfn;
		}

		writel(PAGE_SIZE, vm_dev->base + VIRTIO_MMIO_QUEUE_ALIGN);
		writel(q_pfn, vm_dev->base + VIRTIO_MMIO_QUEUE_PFN);
	} else {
		u64 addr;

		addr = virtqueue_get_desc_addr(vq);
		writel((u32)addr, vm_dev->base + VIRTIO_MMIO_QUEUE_DESC_LOW);
		writel((u32)(addr >> 32),
				vm_dev->base + VIRTIO_MMIO_QUEUE_DESC_HIGH);

		addr = virtqueue_get_avail_addr(vq);
		writel((u32)addr, vm_dev->base + VIRTIO_MMIO_QUEUE_AVAIL_LOW);
		writel((u32)(addr >> 32),
				vm_dev->base + VIRTIO_MMIO_QUEUE_AVAIL_HIGH);

		addr = virtqueue_get_used_addr(vq);
		writel((u32)addr, vm_dev->base + VIRTIO_MMIO_QUEUE_USED_LOW);
		writel((u32)(addr >> 32),
				vm_dev->base + VIRTIO_MMIO_QUEUE_USED_HIGH);

		writel(1, vm_dev->base + VIRTIO_MMIO_QUEUE_READY);
	}

	vq->priv = info;
	info->vq = vq;

	spin_lock_irqsave(&vm_dev->lock, flags);
	list_add(&info->node, &vm_dev->virtqueues);
	spin_unlock_irqrestore(&vm_dev->lock, flags);

	return vq;

error_bad_pfn:
	vring_del_virtqueue(vq);
error_new_virtqueue:
	if (vm_dev->version == 1) {
		writel(0, vm_dev->base + VIRTIO_MMIO_QUEUE_PFN);
	} else {
		writel(0, vm_dev->base + VIRTIO_MMIO_QUEUE_READY);
		WARN_ON(readl(vm_dev->base + VIRTIO_MMIO_QUEUE_READY));
	}
	kfree(info);
error_kmalloc:
error_available:
	return ERR_PTR(err);
}