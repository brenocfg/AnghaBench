#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int io_modes; int buf_struct_size; int min_buffers_needed; int /*<<< orphan*/ * dev; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct atmel_isi* drv_priv; int /*<<< orphan*/ * lock; int /*<<< orphan*/  type; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct frame_buffer {int dummy; } ;
struct fbd {int dummy; } ;
struct TYPE_6__ {int data_width_flags; } ;
struct atmel_isi {int width_flags; int irq; int /*<<< orphan*/  v4l2_dev; TYPE_3__* vdev; scalar_t__ fb_descriptors_phys; scalar_t__ p_fb_descriptors; TYPE_1__ pdata; int /*<<< orphan*/  regs; int /*<<< orphan*/  dma_desc_head; TYPE_2__* dma_desc; int /*<<< orphan*/  lock; struct vb2_queue queue; int /*<<< orphan*/  video_buffer_list; int /*<<< orphan*/  irqlock; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * active; int /*<<< orphan*/  pclk; } ;
struct TYPE_8__ {int device_caps; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/  (* release ) (TYPE_3__*) ;int /*<<< orphan*/  name; struct vb2_queue* queue; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * fops; } ;
struct TYPE_7__ {int /*<<< orphan*/  list; scalar_t__ fbd_phys; scalar_t__ p_fbd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int ISI_DATAWIDTH_10 ; 
 int ISI_DATAWIDTH_8 ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int VIDEO_MAX_FRAME ; 
 int atmel_isi_parse_dt (struct atmel_isi*,struct platform_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct atmel_isi* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct atmel_isi*) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  isi_fops ; 
 int isi_graph_init (struct atmel_isi*) ; 
 int /*<<< orphan*/  isi_interrupt ; 
 int /*<<< orphan*/  isi_ioctl_ops ; 
 int /*<<< orphan*/  isi_video_qops ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct atmel_isi*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 TYPE_3__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (TYPE_3__*) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_3__*,struct atmel_isi*) ; 

__attribute__((used)) static int atmel_isi_probe(struct platform_device *pdev)
{
	int irq;
	struct atmel_isi *isi;
	struct vb2_queue *q;
	struct resource *regs;
	int ret, i;

	isi = devm_kzalloc(&pdev->dev, sizeof(struct atmel_isi), GFP_KERNEL);
	if (!isi)
		return -ENOMEM;

	isi->pclk = devm_clk_get(&pdev->dev, "isi_clk");
	if (IS_ERR(isi->pclk))
		return PTR_ERR(isi->pclk);

	ret = atmel_isi_parse_dt(isi, pdev);
	if (ret)
		return ret;

	isi->active = NULL;
	isi->dev = &pdev->dev;
	mutex_init(&isi->lock);
	spin_lock_init(&isi->irqlock);
	INIT_LIST_HEAD(&isi->video_buffer_list);
	INIT_LIST_HEAD(&isi->dma_desc_head);

	q = &isi->queue;

	/* Initialize the top-level structure */
	ret = v4l2_device_register(&pdev->dev, &isi->v4l2_dev);
	if (ret)
		return ret;

	isi->vdev = video_device_alloc();
	if (!isi->vdev) {
		ret = -ENOMEM;
		goto err_vdev_alloc;
	}

	/* video node */
	isi->vdev->fops = &isi_fops;
	isi->vdev->v4l2_dev = &isi->v4l2_dev;
	isi->vdev->queue = &isi->queue;
	strscpy(isi->vdev->name, KBUILD_MODNAME, sizeof(isi->vdev->name));
	isi->vdev->release = video_device_release;
	isi->vdev->ioctl_ops = &isi_ioctl_ops;
	isi->vdev->lock = &isi->lock;
	isi->vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
		V4L2_CAP_READWRITE;
	video_set_drvdata(isi->vdev, isi);

	/* buffer queue */
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_READ | VB2_DMABUF;
	q->lock = &isi->lock;
	q->drv_priv = isi;
	q->buf_struct_size = sizeof(struct frame_buffer);
	q->ops = &isi_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 2;
	q->dev = &pdev->dev;

	ret = vb2_queue_init(q);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to initialize VB2 queue\n");
		goto err_vb2_queue;
	}
	isi->p_fb_descriptors = dma_alloc_coherent(&pdev->dev,
				sizeof(struct fbd) * VIDEO_MAX_FRAME,
				&isi->fb_descriptors_phys,
				GFP_KERNEL);
	if (!isi->p_fb_descriptors) {
		dev_err(&pdev->dev, "Can't allocate descriptors!\n");
		ret = -ENOMEM;
		goto err_dma_alloc;
	}

	for (i = 0; i < VIDEO_MAX_FRAME; i++) {
		isi->dma_desc[i].p_fbd = isi->p_fb_descriptors + i;
		isi->dma_desc[i].fbd_phys = isi->fb_descriptors_phys +
					i * sizeof(struct fbd);
		list_add(&isi->dma_desc[i].list, &isi->dma_desc_head);
	}

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	isi->regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(isi->regs)) {
		ret = PTR_ERR(isi->regs);
		goto err_ioremap;
	}

	if (isi->pdata.data_width_flags & ISI_DATAWIDTH_8)
		isi->width_flags = 1 << 7;
	if (isi->pdata.data_width_flags & ISI_DATAWIDTH_10)
		isi->width_flags |= 1 << 9;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto err_req_irq;
	}

	ret = devm_request_irq(&pdev->dev, irq, isi_interrupt, 0, "isi", isi);
	if (ret) {
		dev_err(&pdev->dev, "Unable to request irq %d\n", irq);
		goto err_req_irq;
	}
	isi->irq = irq;

	ret = isi_graph_init(isi);
	if (ret < 0)
		goto err_req_irq;

	pm_suspend_ignore_children(&pdev->dev, true);
	pm_runtime_enable(&pdev->dev);
	platform_set_drvdata(pdev, isi);
	return 0;

err_req_irq:
err_ioremap:
	dma_free_coherent(&pdev->dev,
			sizeof(struct fbd) * VIDEO_MAX_FRAME,
			isi->p_fb_descriptors,
			isi->fb_descriptors_phys);
err_dma_alloc:
err_vb2_queue:
	video_device_release(isi->vdev);
err_vdev_alloc:
	v4l2_device_unregister(&isi->v4l2_dev);

	return ret;
}