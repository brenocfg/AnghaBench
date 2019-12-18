#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  va; void* len; void* pa; } ;
struct TYPE_9__ {int /*<<< orphan*/  va; void* len; void* pa; } ;
struct mic_device {int id; TYPE_5__ mmio; TYPE_4__ aper; int /*<<< orphan*/  cosm_dev; TYPE_3__* pdev; TYPE_2__* intr_ops; TYPE_1__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* intr_init ) (struct mic_device*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  aper_bar; int /*<<< orphan*/  mmio_bar; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIC_MAX_NUM_DEVS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cosm_hw_ops ; 
 int /*<<< orphan*/  cosm_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  g_mic_ida ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ioremap_wc (void*,void*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mic_device*) ; 
 struct mic_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mic_bootparam_init (struct mic_device*) ; 
 int /*<<< orphan*/  mic_create_debug_dir (struct mic_device*) ; 
 int /*<<< orphan*/  mic_delete_debug_dir (struct mic_device*) ; 
 int /*<<< orphan*/  mic_device_init (struct mic_device*,struct pci_dev*) ; 
 int mic_dp_init (struct mic_device*) ; 
 int /*<<< orphan*/  mic_dp_uninit (struct mic_device*) ; 
 int /*<<< orphan*/  mic_driver_name ; 
 int /*<<< orphan*/  mic_free_interrupts (struct mic_device*,struct pci_dev*) ; 
 int mic_setup_interrupts (struct mic_device*,struct pci_dev*) ; 
 int mic_smpt_init (struct mic_device*) ; 
 int /*<<< orphan*/  mic_smpt_uninit (struct mic_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 void* pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 void* pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct mic_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct mic_device*) ; 

__attribute__((used)) static int mic_probe(struct pci_dev *pdev,
		     const struct pci_device_id *ent)
{
	int rc;
	struct mic_device *mdev;

	mdev = kzalloc(sizeof(*mdev), GFP_KERNEL);
	if (!mdev) {
		rc = -ENOMEM;
		dev_err(&pdev->dev, "mdev kmalloc failed rc %d\n", rc);
		goto mdev_alloc_fail;
	}
	mdev->id = ida_simple_get(&g_mic_ida, 0, MIC_MAX_NUM_DEVS, GFP_KERNEL);
	if (mdev->id < 0) {
		rc = mdev->id;
		dev_err(&pdev->dev, "ida_simple_get failed rc %d\n", rc);
		goto ida_fail;
	}

	mic_device_init(mdev, pdev);

	rc = pci_enable_device(pdev);
	if (rc) {
		dev_err(&pdev->dev, "failed to enable pci device.\n");
		goto ida_remove;
	}

	pci_set_master(pdev);

	rc = pci_request_regions(pdev, mic_driver_name);
	if (rc) {
		dev_err(&pdev->dev, "failed to get pci regions.\n");
		goto disable_device;
	}

	rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	if (rc) {
		dev_err(&pdev->dev, "Cannot set DMA mask\n");
		goto release_regions;
	}

	mdev->mmio.pa = pci_resource_start(pdev, mdev->ops->mmio_bar);
	mdev->mmio.len = pci_resource_len(pdev, mdev->ops->mmio_bar);
	mdev->mmio.va = pci_ioremap_bar(pdev, mdev->ops->mmio_bar);
	if (!mdev->mmio.va) {
		dev_err(&pdev->dev, "Cannot remap MMIO BAR\n");
		rc = -EIO;
		goto release_regions;
	}

	mdev->aper.pa = pci_resource_start(pdev, mdev->ops->aper_bar);
	mdev->aper.len = pci_resource_len(pdev, mdev->ops->aper_bar);
	mdev->aper.va = ioremap_wc(mdev->aper.pa, mdev->aper.len);
	if (!mdev->aper.va) {
		dev_err(&pdev->dev, "Cannot remap Aperture BAR\n");
		rc = -EIO;
		goto unmap_mmio;
	}

	mdev->intr_ops->intr_init(mdev);
	rc = mic_setup_interrupts(mdev, pdev);
	if (rc) {
		dev_err(&pdev->dev, "mic_setup_interrupts failed %d\n", rc);
		goto unmap_aper;
	}
	rc = mic_smpt_init(mdev);
	if (rc) {
		dev_err(&pdev->dev, "smpt_init failed %d\n", rc);
		goto free_interrupts;
	}

	pci_set_drvdata(pdev, mdev);

	rc = mic_dp_init(mdev);
	if (rc) {
		dev_err(&pdev->dev, "mic_dp_init failed rc %d\n", rc);
		goto smpt_uninit;
	}
	mic_bootparam_init(mdev);
	mic_create_debug_dir(mdev);

	mdev->cosm_dev = cosm_register_device(&mdev->pdev->dev, &cosm_hw_ops);
	if (IS_ERR(mdev->cosm_dev)) {
		rc = PTR_ERR(mdev->cosm_dev);
		dev_err(&pdev->dev, "cosm_add_device failed rc %d\n", rc);
		goto cleanup_debug_dir;
	}
	return 0;
cleanup_debug_dir:
	mic_delete_debug_dir(mdev);
	mic_dp_uninit(mdev);
smpt_uninit:
	mic_smpt_uninit(mdev);
free_interrupts:
	mic_free_interrupts(mdev, pdev);
unmap_aper:
	iounmap(mdev->aper.va);
unmap_mmio:
	iounmap(mdev->mmio.va);
release_regions:
	pci_release_regions(pdev);
disable_device:
	pci_disable_device(pdev);
ida_remove:
	ida_simple_remove(&g_mic_ida, mdev->id);
ida_fail:
	kfree(mdev);
mdev_alloc_fail:
	dev_err(&pdev->dev, "Probe failed rc %d\n", rc);
	return rc;
}