#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  release; struct device* parent; } ;
struct TYPE_7__ {int device; } ;
struct virtio_device {TYPE_3__ dev; int /*<<< orphan*/ * config; TYPE_2__ id; } ;
struct device {int dummy; } ;
struct rproc_vdev {int /*<<< orphan*/  refcount; int /*<<< orphan*/  index; struct device dev; struct rproc* rproc; } ;
struct rproc_mem_entry {int of_resm_idx; int /*<<< orphan*/  len; int /*<<< orphan*/  da; scalar_t__ dma; scalar_t__ va; } ;
struct TYPE_9__ {TYPE_1__* parent; } ;
struct rproc {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_6__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 int dma_declare_coherent_memory (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (TYPE_4__*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct virtio_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_reserved_mem_device_init_by_idx (struct device*,struct device_node*,int) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 int register_virtio_device (struct virtio_device*) ; 
 struct rproc_mem_entry* rproc_find_carveout_by_name (struct rproc*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rproc_va_to_pa (scalar_t__) ; 
 int /*<<< orphan*/  rproc_virtio_config_ops ; 
 int /*<<< orphan*/  rproc_virtio_dev_release ; 

int rproc_add_virtio_dev(struct rproc_vdev *rvdev, int id)
{
	struct rproc *rproc = rvdev->rproc;
	struct device *dev = &rvdev->dev;
	struct virtio_device *vdev;
	struct rproc_mem_entry *mem;
	int ret;

	/* Try to find dedicated vdev buffer carveout */
	mem = rproc_find_carveout_by_name(rproc, "vdev%dbuffer", rvdev->index);
	if (mem) {
		phys_addr_t pa;

		if (mem->of_resm_idx != -1) {
			struct device_node *np = rproc->dev.parent->of_node;

			/* Associate reserved memory to vdev device */
			ret = of_reserved_mem_device_init_by_idx(dev, np,
								 mem->of_resm_idx);
			if (ret) {
				dev_err(dev, "Can't associate reserved memory\n");
				goto out;
			}
		} else {
			if (mem->va) {
				dev_warn(dev, "vdev %d buffer already mapped\n",
					 rvdev->index);
				pa = rproc_va_to_pa(mem->va);
			} else {
				/* Use dma address as carveout no memmapped yet */
				pa = (phys_addr_t)mem->dma;
			}

			/* Associate vdev buffer memory pool to vdev subdev */
			ret = dma_declare_coherent_memory(dev, pa,
							   mem->da,
							   mem->len);
			if (ret < 0) {
				dev_err(dev, "Failed to associate buffer\n");
				goto out;
			}
		}
	}

	/* Allocate virtio device */
	vdev = kzalloc(sizeof(*vdev), GFP_KERNEL);
	if (!vdev) {
		ret = -ENOMEM;
		goto out;
	}
	vdev->id.device	= id,
	vdev->config = &rproc_virtio_config_ops,
	vdev->dev.parent = dev;
	vdev->dev.release = rproc_virtio_dev_release;

	/*
	 * We're indirectly making a non-temporary copy of the rproc pointer
	 * here, because drivers probed with this vdev will indirectly
	 * access the wrapping rproc.
	 *
	 * Therefore we must increment the rproc refcount here, and decrement
	 * it _only_ when the vdev is released.
	 */
	get_device(&rproc->dev);

	/* Reference the vdev and vring allocations */
	kref_get(&rvdev->refcount);

	ret = register_virtio_device(vdev);
	if (ret) {
		put_device(&vdev->dev);
		dev_err(dev, "failed to register vdev: %d\n", ret);
		goto out;
	}

	dev_info(dev, "registered %s (type %d)\n", dev_name(&vdev->dev), id);

out:
	return ret;
}