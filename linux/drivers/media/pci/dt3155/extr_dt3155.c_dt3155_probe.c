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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  minor; TYPE_3__* queue; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * v4l2_dev; } ;
struct TYPE_6__ {int io_modes; int min_buffers_needed; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  gfp_flags; struct dt3155_priv* drv_priv; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/  type; } ;
struct dt3155_priv {int width; int height; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  regs; struct pci_dev* pdev; TYPE_1__ vdev; int /*<<< orphan*/  config; int /*<<< orphan*/  lock; TYPE_3__ vidq; int /*<<< orphan*/  mux; int /*<<< orphan*/  dmaq; int /*<<< orphan*/  csr2; int /*<<< orphan*/  std; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQ_MODE_EVEN ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DT3155_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_DMA32 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_STD_625_50 ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VT_50HZ ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct dt3155_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dt3155_init_board (struct dt3155_priv*) ; 
 int /*<<< orphan*/  dt3155_irq_handler_even ; 
 TYPE_1__ dt3155_vdev ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct dt3155_priv*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_request_region (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_ops ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dt3155_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (TYPE_3__*) ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct dt3155_priv*) ; 

__attribute__((used)) static int dt3155_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int err;
	struct dt3155_priv *pd;

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (err)
		return -ENODEV;
	pd = devm_kzalloc(&pdev->dev, sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return -ENOMEM;

	err = v4l2_device_register(&pdev->dev, &pd->v4l2_dev);
	if (err)
		return err;
	pd->vdev = dt3155_vdev;
	pd->vdev.v4l2_dev = &pd->v4l2_dev;
	video_set_drvdata(&pd->vdev, pd);  /* for use in video_fops */
	pd->pdev = pdev;
	pd->std = V4L2_STD_625_50;
	pd->csr2 = VT_50HZ;
	pd->width = 768;
	pd->height = 576;
	INIT_LIST_HEAD(&pd->dmaq);
	mutex_init(&pd->mux);
	pd->vdev.lock = &pd->mux; /* for locking v4l2_file_operations */
	pd->vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	pd->vidq.timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	pd->vidq.io_modes = VB2_MMAP | VB2_DMABUF | VB2_READ;
	pd->vidq.ops = &q_ops;
	pd->vidq.mem_ops = &vb2_dma_contig_memops;
	pd->vidq.drv_priv = pd;
	pd->vidq.min_buffers_needed = 2;
	pd->vidq.gfp_flags = GFP_DMA32;
	pd->vidq.lock = &pd->mux; /* for locking v4l2_file_operations */
	pd->vidq.dev = &pdev->dev;
	pd->vdev.queue = &pd->vidq;
	err = vb2_queue_init(&pd->vidq);
	if (err < 0)
		goto err_v4l2_dev_unreg;
	spin_lock_init(&pd->lock);
	pd->config = ACQ_MODE_EVEN;
	err = pci_enable_device(pdev);
	if (err)
		goto err_v4l2_dev_unreg;
	err = pci_request_region(pdev, 0, pci_name(pdev));
	if (err)
		goto err_pci_disable;
	pd->regs = pci_iomap(pdev, 0, pci_resource_len(pd->pdev, 0));
	if (!pd->regs) {
		err = -ENOMEM;
		goto err_free_reg;
	}
	err = dt3155_init_board(pd);
	if (err)
		goto err_iounmap;
	err = request_irq(pd->pdev->irq, dt3155_irq_handler_even,
					IRQF_SHARED, DT3155_NAME, pd);
	if (err)
		goto err_iounmap;
	err = video_register_device(&pd->vdev, VFL_TYPE_GRABBER, -1);
	if (err)
		goto err_free_irq;
	dev_info(&pdev->dev, "/dev/video%i is ready\n", pd->vdev.minor);
	return 0;  /*   success   */

err_free_irq:
	free_irq(pd->pdev->irq, pd);
err_iounmap:
	pci_iounmap(pdev, pd->regs);
err_free_reg:
	pci_release_region(pdev, 0);
err_pci_disable:
	pci_disable_device(pdev);
err_v4l2_dev_unreg:
	v4l2_device_unregister(&pd->v4l2_dev);
	return err;
}