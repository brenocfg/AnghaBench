#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {unsigned long driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct nvme_queue {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; int /*<<< orphan*/  reset_work; } ;
struct nvme_dev {struct nvme_dev* queues; int /*<<< orphan*/  dev; int /*<<< orphan*/  iod_mempool; TYPE_1__ ctrl; int /*<<< orphan*/  shutdown_lock; int /*<<< orphan*/  remove_work; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NUMA_NO_NODE ; 
 int /*<<< orphan*/  NVME_MAX_KB_SZ ; 
 int /*<<< orphan*/  NVME_MAX_SEGS ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  async_schedule (int /*<<< orphan*/ ,struct nvme_dev*) ; 
 unsigned long check_vendor_combination_bug (struct pci_dev*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  first_memory_node ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 struct nvme_dev* kcalloc_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct nvme_dev*) ; 
 struct nvme_dev* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max_queue_count () ; 
 int /*<<< orphan*/  mempool_create_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_kfree ; 
 int /*<<< orphan*/  mempool_kmalloc ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_async_probe ; 
 int nvme_dev_map (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_dev_unmap (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_get_ctrl (TYPE_1__*) ; 
 int nvme_init_ctrl (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  nvme_pci_ctrl_ops ; 
 size_t nvme_pci_iod_alloc_size (struct nvme_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_release_prp_pools (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_remove_dead_ctrl_work ; 
 int /*<<< orphan*/  nvme_reset_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_reset_work ; 
 int nvme_setup_prp_pools (struct nvme_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct nvme_dev*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dev_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int node, result = -ENOMEM;
	struct nvme_dev *dev;
	unsigned long quirks = id->driver_data;
	size_t alloc_size;

	node = dev_to_node(&pdev->dev);
	if (node == NUMA_NO_NODE)
		set_dev_node(&pdev->dev, first_memory_node);

	dev = kzalloc_node(sizeof(*dev), GFP_KERNEL, node);
	if (!dev)
		return -ENOMEM;

	dev->queues = kcalloc_node(max_queue_count(), sizeof(struct nvme_queue),
					GFP_KERNEL, node);
	if (!dev->queues)
		goto free;

	dev->dev = get_device(&pdev->dev);
	pci_set_drvdata(pdev, dev);

	result = nvme_dev_map(dev);
	if (result)
		goto put_pci;

	INIT_WORK(&dev->ctrl.reset_work, nvme_reset_work);
	INIT_WORK(&dev->remove_work, nvme_remove_dead_ctrl_work);
	mutex_init(&dev->shutdown_lock);

	result = nvme_setup_prp_pools(dev);
	if (result)
		goto unmap;

	quirks |= check_vendor_combination_bug(pdev);

	/*
	 * Double check that our mempool alloc size will cover the biggest
	 * command we support.
	 */
	alloc_size = nvme_pci_iod_alloc_size(dev, NVME_MAX_KB_SZ,
						NVME_MAX_SEGS, true);
	WARN_ON_ONCE(alloc_size > PAGE_SIZE);

	dev->iod_mempool = mempool_create_node(1, mempool_kmalloc,
						mempool_kfree,
						(void *) alloc_size,
						GFP_KERNEL, node);
	if (!dev->iod_mempool) {
		result = -ENOMEM;
		goto release_pools;
	}

	result = nvme_init_ctrl(&dev->ctrl, &pdev->dev, &nvme_pci_ctrl_ops,
			quirks);
	if (result)
		goto release_mempool;

	dev_info(dev->ctrl.device, "pci function %s\n", dev_name(&pdev->dev));

	nvme_reset_ctrl(&dev->ctrl);
	nvme_get_ctrl(&dev->ctrl);
	async_schedule(nvme_async_probe, dev);

	return 0;

 release_mempool:
	mempool_destroy(dev->iod_mempool);
 release_pools:
	nvme_release_prp_pools(dev);
 unmap:
	nvme_dev_unmap(dev);
 put_pci:
	put_device(dev->dev);
 free:
	kfree(dev->queues);
	kfree(dev);
	return result;
}