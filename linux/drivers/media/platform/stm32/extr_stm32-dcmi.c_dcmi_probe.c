#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_17__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
struct vb2_queue {int io_modes; int buf_struct_size; int min_buffers_needed; TYPE_10__* dev; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct stm32_dcmi* drv_priv; int /*<<< orphan*/ * lock; int /*<<< orphan*/  type; } ;
struct TYPE_35__ {int /*<<< orphan*/  data_shift; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  flags; } ;
struct TYPE_34__ {TYPE_3__ parallel; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_2__ bus; } ;
struct TYPE_32__ {TYPE_10__* dev; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  model; } ;
struct TYPE_37__ {TYPE_17__* mdev; } ;
struct TYPE_31__ {int /*<<< orphan*/  flags; } ;
struct TYPE_33__ {int /*<<< orphan*/  data_shift; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  flags; } ;
struct stm32_dcmi {struct dma_chan* dma_chan; TYPE_17__ mdev; TYPE_9__ v4l2_dev; TYPE_4__* vdev; int /*<<< orphan*/  notifier; struct clk* rstc; int /*<<< orphan*/  lock; TYPE_10__* dev; TYPE_15__ vid_cap_pad; struct vb2_queue queue; int /*<<< orphan*/  state; struct clk* mclk; int /*<<< orphan*/  buffers; int /*<<< orphan*/  complete; int /*<<< orphan*/  dma_lock; int /*<<< orphan*/  irqlock; struct clk* regs; int /*<<< orphan*/  res; TYPE_1__ bus; } ;
struct TYPE_29__ {struct device_node* of_node; } ;
struct platform_device {TYPE_10__ dev; } ;
struct of_device_id {int dummy; } ;
struct dma_chan {int dummy; } ;
struct device_node {int dummy; } ;
struct dcmi_buf {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_30__ {int /*<<< orphan*/  flags; } ;
struct TYPE_36__ {int device_caps; TYPE_14__ entity; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/  (* release ) (TYPE_4__*) ;int /*<<< orphan*/  name; struct vb2_queue* queue; TYPE_9__* v4l2_dev; int /*<<< orphan*/ * fops; } ;

/* Variables and functions */
 char* DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 char* KBUILD_MODNAME ; 
 int /*<<< orphan*/  MEDIA_ENT_FL_DEFAULT ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  STOPPED ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_MBUS_CSI2_DPHY ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dcmi_fops ; 
 int dcmi_graph_init (struct stm32_dcmi*) ; 
 int /*<<< orphan*/  dcmi_ioctl_ops ; 
 int /*<<< orphan*/  dcmi_irq_callback ; 
 int /*<<< orphan*/  dcmi_irq_thread ; 
 int /*<<< orphan*/  dcmi_video_qops ; 
 int /*<<< orphan*/  dev_dbg (TYPE_10__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_10__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_10__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_10__*) ; 
 struct clk* devm_clk_get (TYPE_10__*,char*) ; 
 struct clk* devm_ioremap_resource (TYPE_10__*,int /*<<< orphan*/ ) ; 
 struct stm32_dcmi* devm_kzalloc (TYPE_10__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_10__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stm32_dcmi*) ; 
 struct clk* devm_reset_control_get_exclusive (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_release_channel (struct dma_chan*) ; 
 struct dma_chan* dma_request_slave_channel (TYPE_10__*,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_cleanup (TYPE_17__*) ; 
 int /*<<< orphan*/  media_device_init (TYPE_17__*) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_14__*) ; 
 int media_entity_pads_init (TYPE_14__*,int,TYPE_15__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_dcmi*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_10__*) ; 
 int reset_control_assert (struct clk*) ; 
 int reset_control_deassert (struct clk*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_dcmi_of_match ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int v4l2_device_register (TYPE_10__*,TYPE_9__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_9__*) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 TYPE_4__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_4__*) ; 
 int /*<<< orphan*/  video_device_release (TYPE_4__*) ; 
 int video_register_device (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_4__*,struct stm32_dcmi*) ; 

__attribute__((used)) static int dcmi_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	const struct of_device_id *match = NULL;
	struct v4l2_fwnode_endpoint ep = { .bus_type = 0 };
	struct stm32_dcmi *dcmi;
	struct vb2_queue *q;
	struct dma_chan *chan;
	struct clk *mclk;
	int irq;
	int ret = 0;

	match = of_match_device(of_match_ptr(stm32_dcmi_of_match), &pdev->dev);
	if (!match) {
		dev_err(&pdev->dev, "Could not find a match in devicetree\n");
		return -ENODEV;
	}

	dcmi = devm_kzalloc(&pdev->dev, sizeof(struct stm32_dcmi), GFP_KERNEL);
	if (!dcmi)
		return -ENOMEM;

	dcmi->rstc = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (IS_ERR(dcmi->rstc)) {
		dev_err(&pdev->dev, "Could not get reset control\n");
		return PTR_ERR(dcmi->rstc);
	}

	/* Get bus characteristics from devicetree */
	np = of_graph_get_next_endpoint(np, NULL);
	if (!np) {
		dev_err(&pdev->dev, "Could not find the endpoint\n");
		return -ENODEV;
	}

	ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(np), &ep);
	of_node_put(np);
	if (ret) {
		dev_err(&pdev->dev, "Could not parse the endpoint\n");
		return ret;
	}

	if (ep.bus_type == V4L2_MBUS_CSI2_DPHY) {
		dev_err(&pdev->dev, "CSI bus not supported\n");
		return -ENODEV;
	}
	dcmi->bus.flags = ep.bus.parallel.flags;
	dcmi->bus.bus_width = ep.bus.parallel.bus_width;
	dcmi->bus.data_shift = ep.bus.parallel.data_shift;

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return irq ? irq : -ENXIO;

	dcmi->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!dcmi->res) {
		dev_err(&pdev->dev, "Could not get resource\n");
		return -ENODEV;
	}

	dcmi->regs = devm_ioremap_resource(&pdev->dev, dcmi->res);
	if (IS_ERR(dcmi->regs)) {
		dev_err(&pdev->dev, "Could not map registers\n");
		return PTR_ERR(dcmi->regs);
	}

	ret = devm_request_threaded_irq(&pdev->dev, irq, dcmi_irq_callback,
					dcmi_irq_thread, IRQF_ONESHOT,
					dev_name(&pdev->dev), dcmi);
	if (ret) {
		dev_err(&pdev->dev, "Unable to request irq %d\n", irq);
		return ret;
	}

	mclk = devm_clk_get(&pdev->dev, "mclk");
	if (IS_ERR(mclk)) {
		if (PTR_ERR(mclk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Unable to get mclk\n");
		return PTR_ERR(mclk);
	}

	chan = dma_request_slave_channel(&pdev->dev, "tx");
	if (!chan) {
		dev_info(&pdev->dev, "Unable to request DMA channel, defer probing\n");
		return -EPROBE_DEFER;
	}

	spin_lock_init(&dcmi->irqlock);
	mutex_init(&dcmi->lock);
	mutex_init(&dcmi->dma_lock);
	init_completion(&dcmi->complete);
	INIT_LIST_HEAD(&dcmi->buffers);

	dcmi->dev = &pdev->dev;
	dcmi->mclk = mclk;
	dcmi->state = STOPPED;
	dcmi->dma_chan = chan;

	q = &dcmi->queue;

	dcmi->v4l2_dev.mdev = &dcmi->mdev;

	/* Initialize media device */
	strscpy(dcmi->mdev.model, DRV_NAME, sizeof(dcmi->mdev.model));
	snprintf(dcmi->mdev.bus_info, sizeof(dcmi->mdev.bus_info),
		 "platform:%s", DRV_NAME);
	dcmi->mdev.dev = &pdev->dev;
	media_device_init(&dcmi->mdev);

	/* Initialize the top-level structure */
	ret = v4l2_device_register(&pdev->dev, &dcmi->v4l2_dev);
	if (ret)
		goto err_media_device_cleanup;

	dcmi->vdev = video_device_alloc();
	if (!dcmi->vdev) {
		ret = -ENOMEM;
		goto err_device_unregister;
	}

	/* Video node */
	dcmi->vdev->fops = &dcmi_fops;
	dcmi->vdev->v4l2_dev = &dcmi->v4l2_dev;
	dcmi->vdev->queue = &dcmi->queue;
	strscpy(dcmi->vdev->name, KBUILD_MODNAME, sizeof(dcmi->vdev->name));
	dcmi->vdev->release = video_device_release;
	dcmi->vdev->ioctl_ops = &dcmi_ioctl_ops;
	dcmi->vdev->lock = &dcmi->lock;
	dcmi->vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
				  V4L2_CAP_READWRITE;
	video_set_drvdata(dcmi->vdev, dcmi);

	/* Media entity pads */
	dcmi->vid_cap_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dcmi->vdev->entity,
				     1, &dcmi->vid_cap_pad);
	if (ret) {
		dev_err(dcmi->dev, "Failed to init media entity pad\n");
		goto err_device_release;
	}
	dcmi->vdev->entity.flags |= MEDIA_ENT_FL_DEFAULT;

	ret = video_register_device(dcmi->vdev, VFL_TYPE_GRABBER, -1);
	if (ret) {
		dev_err(dcmi->dev, "Failed to register video device\n");
		goto err_media_entity_cleanup;
	}

	dev_dbg(dcmi->dev, "Device registered as %s\n",
		video_device_node_name(dcmi->vdev));

	/* Buffer queue */
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_READ | VB2_DMABUF;
	q->lock = &dcmi->lock;
	q->drv_priv = dcmi;
	q->buf_struct_size = sizeof(struct dcmi_buf);
	q->ops = &dcmi_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 2;
	q->dev = &pdev->dev;

	ret = vb2_queue_init(q);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to initialize vb2 queue\n");
		goto err_media_entity_cleanup;
	}

	ret = dcmi_graph_init(dcmi);
	if (ret < 0)
		goto err_media_entity_cleanup;

	/* Reset device */
	ret = reset_control_assert(dcmi->rstc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to assert the reset line\n");
		goto err_cleanup;
	}

	usleep_range(3000, 5000);

	ret = reset_control_deassert(dcmi->rstc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to deassert the reset line\n");
		goto err_cleanup;
	}

	dev_info(&pdev->dev, "Probe done\n");

	platform_set_drvdata(pdev, dcmi);

	pm_runtime_enable(&pdev->dev);

	return 0;

err_cleanup:
	v4l2_async_notifier_cleanup(&dcmi->notifier);
err_media_entity_cleanup:
	media_entity_cleanup(&dcmi->vdev->entity);
err_device_release:
	video_device_release(dcmi->vdev);
err_device_unregister:
	v4l2_device_unregister(&dcmi->v4l2_dev);
err_media_device_cleanup:
	media_device_cleanup(&dcmi->mdev);
	dma_release_channel(dcmi->dma_chan);

	return ret;
}