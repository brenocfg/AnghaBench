#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int io_modes; int buf_struct_size; int min_buffers_needed; TYPE_7__* dev; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct stm32_dcmi* drv_priv; int /*<<< orphan*/ * lock; int /*<<< orphan*/  type; } ;
struct TYPE_20__ {int /*<<< orphan*/  data_shift; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  flags; } ;
struct TYPE_21__ {TYPE_2__ parallel; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_3__ bus; } ;
struct TYPE_19__ {int /*<<< orphan*/  data_shift; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  flags; } ;
struct stm32_dcmi {struct dma_chan* dma_chan; int /*<<< orphan*/  v4l2_dev; TYPE_4__* vdev; struct clk* rstc; int /*<<< orphan*/  lock; struct vb2_queue queue; int /*<<< orphan*/  state; struct clk* mclk; TYPE_7__* dev; int /*<<< orphan*/  buffers; int /*<<< orphan*/  complete; int /*<<< orphan*/  irqlock; struct clk* regs; int /*<<< orphan*/  res; TYPE_1__ bus; } ;
struct TYPE_23__ {struct device_node* of_node; } ;
struct platform_device {TYPE_7__ dev; } ;
struct of_device_id {int dummy; } ;
struct dma_chan {int dummy; } ;
struct device_node {int dummy; } ;
struct dcmi_buf {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_22__ {int device_caps; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/  (* release ) (TYPE_4__*) ;int /*<<< orphan*/  name; struct vb2_queue* queue; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * fops; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  STOPPED ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_MBUS_CSI2 ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int /*<<< orphan*/  dcmi_fops ; 
 int dcmi_graph_init (struct stm32_dcmi*) ; 
 int /*<<< orphan*/  dcmi_ioctl_ops ; 
 int /*<<< orphan*/  dcmi_irq_callback ; 
 int /*<<< orphan*/  dcmi_irq_thread ; 
 int /*<<< orphan*/  dcmi_video_qops ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_7__*) ; 
 struct clk* devm_clk_get (TYPE_7__*,char*) ; 
 struct clk* devm_ioremap_resource (TYPE_7__*,int /*<<< orphan*/ ) ; 
 struct stm32_dcmi* devm_kzalloc (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_7__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stm32_dcmi*) ; 
 struct clk* devm_reset_control_get_exclusive (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_release_channel (struct dma_chan*) ; 
 struct dma_chan* dma_request_slave_channel (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_dcmi*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_7__*) ; 
 int reset_control_assert (struct clk*) ; 
 int reset_control_deassert (struct clk*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_dcmi_of_match ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int v4l2_device_register (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 TYPE_4__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (TYPE_4__*) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_4__*,struct stm32_dcmi*) ; 

__attribute__((used)) static int dcmi_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	const struct of_device_id *match = NULL;
	struct v4l2_fwnode_endpoint ep;
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
		return -ENODEV;
	}

	/* Get bus characteristics from devicetree */
	np = of_graph_get_next_endpoint(np, NULL);
	if (!np) {
		dev_err(&pdev->dev, "Could not find the endpoint\n");
		of_node_put(np);
		return -ENODEV;
	}

	ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(np), &ep);
	of_node_put(np);
	if (ret) {
		dev_err(&pdev->dev, "Could not parse the endpoint\n");
		return -ENODEV;
	}

	if (ep.bus_type == V4L2_MBUS_CSI2) {
		dev_err(&pdev->dev, "CSI bus not supported\n");
		return -ENODEV;
	}
	dcmi->bus.flags = ep.bus.parallel.flags;
	dcmi->bus.bus_width = ep.bus.parallel.bus_width;
	dcmi->bus.data_shift = ep.bus.parallel.data_shift;

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		dev_err(&pdev->dev, "Could not get irq\n");
		return -ENODEV;
	}

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
		return -ENODEV;
	}

	mclk = devm_clk_get(&pdev->dev, "mclk");
	if (IS_ERR(mclk)) {
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
	init_completion(&dcmi->complete);
	INIT_LIST_HEAD(&dcmi->buffers);

	dcmi->dev = &pdev->dev;
	dcmi->mclk = mclk;
	dcmi->state = STOPPED;
	dcmi->dma_chan = chan;

	q = &dcmi->queue;

	/* Initialize the top-level structure */
	ret = v4l2_device_register(&pdev->dev, &dcmi->v4l2_dev);
	if (ret)
		goto err_dma_release;

	dcmi->vdev = video_device_alloc();
	if (!dcmi->vdev) {
		ret = -ENOMEM;
		goto err_device_unregister;
	}

	/* Video node */
	dcmi->vdev->fops = &dcmi_fops;
	dcmi->vdev->v4l2_dev = &dcmi->v4l2_dev;
	dcmi->vdev->queue = &dcmi->queue;
	strlcpy(dcmi->vdev->name, KBUILD_MODNAME, sizeof(dcmi->vdev->name));
	dcmi->vdev->release = video_device_release;
	dcmi->vdev->ioctl_ops = &dcmi_ioctl_ops;
	dcmi->vdev->lock = &dcmi->lock;
	dcmi->vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
				  V4L2_CAP_READWRITE;
	video_set_drvdata(dcmi->vdev, dcmi);

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
		goto err_device_release;
	}

	ret = dcmi_graph_init(dcmi);
	if (ret < 0)
		goto err_device_release;

	/* Reset device */
	ret = reset_control_assert(dcmi->rstc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to assert the reset line\n");
		goto err_device_release;
	}

	usleep_range(3000, 5000);

	ret = reset_control_deassert(dcmi->rstc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to deassert the reset line\n");
		goto err_device_release;
	}

	dev_info(&pdev->dev, "Probe done\n");

	platform_set_drvdata(pdev, dcmi);

	pm_runtime_enable(&pdev->dev);

	return 0;

err_device_release:
	video_device_release(dcmi->vdev);
err_device_unregister:
	v4l2_device_unregister(&dcmi->v4l2_dev);
err_dma_release:
	dma_release_channel(dcmi->dma_chan);

	return ret;
}