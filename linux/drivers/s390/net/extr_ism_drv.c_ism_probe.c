#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ism_dev {TYPE_1__* smcd; struct pci_dev* pdev; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct ism_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISM_NR_DMBS ; 
 scalar_t__ SZ_1M ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct ism_dev*) ; 
 int /*<<< orphan*/  dma_set_max_seg_size (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dma_set_seg_boundary (int /*<<< orphan*/ *,scalar_t__) ; 
 int ism_dev_init (struct ism_dev*) ; 
 int /*<<< orphan*/  ism_ops ; 
 int /*<<< orphan*/  kfree (struct ism_dev*) ; 
 struct ism_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int pci_request_mem_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 TYPE_1__* smcd_alloc_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smcd_free_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ism_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct ism_dev *ism;
	int ret;

	ism = kzalloc(sizeof(*ism), GFP_KERNEL);
	if (!ism)
		return -ENOMEM;

	spin_lock_init(&ism->lock);
	dev_set_drvdata(&pdev->dev, ism);
	ism->pdev = pdev;

	ret = pci_enable_device_mem(pdev);
	if (ret)
		goto err;

	ret = pci_request_mem_regions(pdev, DRV_NAME);
	if (ret)
		goto err_disable;

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	if (ret)
		goto err_resource;

	dma_set_seg_boundary(&pdev->dev, SZ_1M - 1);
	dma_set_max_seg_size(&pdev->dev, SZ_1M);
	pci_set_master(pdev);

	ism->smcd = smcd_alloc_dev(&pdev->dev, dev_name(&pdev->dev), &ism_ops,
				   ISM_NR_DMBS);
	if (!ism->smcd)
		goto err_resource;

	ism->smcd->priv = ism;
	ret = ism_dev_init(ism);
	if (ret)
		goto err_free;

	return 0;

err_free:
	smcd_free_dev(ism->smcd);
err_resource:
	pci_release_mem_regions(pdev);
err_disable:
	pci_disable_device(pdev);
err:
	kfree(ism);
	dev_set_drvdata(&pdev->dev, NULL);
	return ret;
}