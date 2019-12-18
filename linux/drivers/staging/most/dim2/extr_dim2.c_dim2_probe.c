#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct resource {int start; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct of_device_id {struct dim2_platform_data* data; } ;
struct most_channel_capability {int direction; int data_type; int /*<<< orphan*/  buffer_size_streaming; int /*<<< orphan*/  num_buffers_streaming; int /*<<< orphan*/  buffer_size_packet; int /*<<< orphan*/  num_buffers_packet; int /*<<< orphan*/  name_suffix; } ;
struct hdm_channel {int is_initialized; int /*<<< orphan*/  name; int /*<<< orphan*/  started_list; int /*<<< orphan*/  pending_list; } ;
struct dim2_platform_data {int (* enable ) (struct platform_device*) ;int /*<<< orphan*/  (* disable ) (struct platform_device*) ;} ;
struct TYPE_9__ {int num_channels; int /*<<< orphan*/  dev; TYPE_4__* driver_dev; int /*<<< orphan*/  request_netinfo; int /*<<< orphan*/  poison_channel; int /*<<< orphan*/  dma_free; int /*<<< orphan*/  dma_alloc; int /*<<< orphan*/  enqueue; int /*<<< orphan*/  configure; struct most_channel_capability* channel_vector; int /*<<< orphan*/  description; int /*<<< orphan*/  interface; } ;
struct TYPE_10__ {char* init_name; int /*<<< orphan*/ * parent; } ;
struct dim2_hdm {int atx_idx; int /*<<< orphan*/  (* disable_platform ) (struct platform_device*) ;int /*<<< orphan*/  netinfo_task; TYPE_1__ most_iface; TYPE_3__ dev; struct most_channel_capability* capabilities; int /*<<< orphan*/  name; struct hdm_channel* hch; scalar_t__ deliver_netinfo; int /*<<< orphan*/  netinfo_waitq; int /*<<< orphan*/  clk_speed; int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 scalar_t__ DIM_NO_ERROR ; 
 int DMA_CHANNELS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITYPE_MEDIALB_DIM2 ; 
 int /*<<< orphan*/  MAX_BUFFERS_PACKET ; 
 int /*<<< orphan*/  MAX_BUFFERS_STREAMING ; 
 int /*<<< orphan*/  MAX_BUF_SIZE_PACKET ; 
 int /*<<< orphan*/  MAX_BUF_SIZE_STREAMING ; 
 int MOST_CH_ASYNC ; 
 int MOST_CH_CONTROL ; 
 int MOST_CH_ISOC ; 
 int MOST_CH_RX ; 
 int MOST_CH_SYNC ; 
 int MOST_CH_TX ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configure_channel ; 
 int /*<<< orphan*/  deliver_netinfo_thread ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct dim2_hdm* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct dim2_hdm*) ; 
 int /*<<< orphan*/  dim2_ahb_isr ; 
 int /*<<< orphan*/  dim2_mlb_isr ; 
 int /*<<< orphan*/  dim2_of_match ; 
 int dim2_sysfs_probe (TYPE_3__*) ; 
 int /*<<< orphan*/  dim_shutdown () ; 
 scalar_t__ dim_startup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc ; 
 int /*<<< orphan*/  dma_free ; 
 int /*<<< orphan*/  enqueue ; 
 int /*<<< orphan*/  fcnt ; 
 int get_dim2_clk_speed (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ *,struct dim2_hdm*,char*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  most_deregister_interface (TYPE_1__*) ; 
 int most_register_interface (TYPE_1__*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_property_read_string (int /*<<< orphan*/ ,char*,char const**) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dim2_hdm*) ; 
 int /*<<< orphan*/  poison_channel ; 
 int /*<<< orphan*/  request_netinfo ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char const*,int) ; 
 int stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  stub2 (struct platform_device*) ; 

__attribute__((used)) static int dim2_probe(struct platform_device *pdev)
{
	const struct dim2_platform_data *pdata;
	const struct of_device_id *of_id;
	const char *clock_speed;
	struct dim2_hdm *dev;
	struct resource *res;
	int ret, i;
	u8 hal_ret;
	int irq;

	enum { MLB_INT_IDX, AHB0_INT_IDX };

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->atx_idx = -1;

	platform_set_drvdata(pdev, dev);

	ret = of_property_read_string(pdev->dev.of_node,
				      "microchip,clock-speed", &clock_speed);
	if (ret) {
		dev_err(&pdev->dev, "missing dt property clock-speed\n");
		return ret;
	}

	ret = get_dim2_clk_speed(clock_speed, &dev->clk_speed);
	if (ret) {
		dev_err(&pdev->dev, "bad dt property clock-speed\n");
		return ret;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dev->io_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(dev->io_base))
		return PTR_ERR(dev->io_base);

	of_id = of_match_node(dim2_of_match, pdev->dev.of_node);
	pdata = of_id->data;
	ret = pdata && pdata->enable ? pdata->enable(pdev) : 0;
	if (ret)
		return ret;

	dev->disable_platform = pdata ? pdata->disable : NULL;

	dev_info(&pdev->dev, "sync: num of frames per sub-buffer: %u\n", fcnt);
	hal_ret = dim_startup(dev->io_base, dev->clk_speed, fcnt);
	if (hal_ret != DIM_NO_ERROR) {
		dev_err(&pdev->dev, "dim_startup failed: %d\n", hal_ret);
		ret = -ENODEV;
		goto err_disable_platform;
	}

	irq = platform_get_irq(pdev, AHB0_INT_IDX);
	if (irq < 0) {
		ret = irq;
		goto err_shutdown_dim;
	}

	ret = devm_request_irq(&pdev->dev, irq, dim2_ahb_isr, 0,
			       "dim2_ahb0_int", dev);
	if (ret) {
		dev_err(&pdev->dev, "failed to request ahb0_int irq %d\n", irq);
		goto err_shutdown_dim;
	}

	irq = platform_get_irq(pdev, MLB_INT_IDX);
	if (irq < 0) {
		ret = irq;
		goto err_shutdown_dim;
	}

	ret = devm_request_irq(&pdev->dev, irq, dim2_mlb_isr, 0,
			       "dim2_mlb_int", dev);
	if (ret) {
		dev_err(&pdev->dev, "failed to request mlb_int irq %d\n", irq);
		goto err_shutdown_dim;
	}

	init_waitqueue_head(&dev->netinfo_waitq);
	dev->deliver_netinfo = 0;
	dev->netinfo_task = kthread_run(&deliver_netinfo_thread, dev,
					"dim2_netinfo");
	if (IS_ERR(dev->netinfo_task)) {
		ret = PTR_ERR(dev->netinfo_task);
		goto err_shutdown_dim;
	}

	for (i = 0; i < DMA_CHANNELS; i++) {
		struct most_channel_capability *cap = dev->capabilities + i;
		struct hdm_channel *hdm_ch = dev->hch + i;

		INIT_LIST_HEAD(&hdm_ch->pending_list);
		INIT_LIST_HEAD(&hdm_ch->started_list);
		hdm_ch->is_initialized = false;
		snprintf(hdm_ch->name, sizeof(hdm_ch->name), "ca%d", i * 2 + 2);

		cap->name_suffix = hdm_ch->name;
		cap->direction = MOST_CH_RX | MOST_CH_TX;
		cap->data_type = MOST_CH_CONTROL | MOST_CH_ASYNC |
				 MOST_CH_ISOC | MOST_CH_SYNC;
		cap->num_buffers_packet = MAX_BUFFERS_PACKET;
		cap->buffer_size_packet = MAX_BUF_SIZE_PACKET;
		cap->num_buffers_streaming = MAX_BUFFERS_STREAMING;
		cap->buffer_size_streaming = MAX_BUF_SIZE_STREAMING;
	}

	{
		const char *fmt;

		if (sizeof(res->start) == sizeof(long long))
			fmt = "dim2-%016llx";
		else if (sizeof(res->start) == sizeof(long))
			fmt = "dim2-%016lx";
		else
			fmt = "dim2-%016x";

		snprintf(dev->name, sizeof(dev->name), fmt, res->start);
	}

	dev->most_iface.interface = ITYPE_MEDIALB_DIM2;
	dev->most_iface.description = dev->name;
	dev->most_iface.num_channels = DMA_CHANNELS;
	dev->most_iface.channel_vector = dev->capabilities;
	dev->most_iface.configure = configure_channel;
	dev->most_iface.enqueue = enqueue;
	dev->most_iface.dma_alloc = dma_alloc;
	dev->most_iface.dma_free = dma_free;
	dev->most_iface.poison_channel = poison_channel;
	dev->most_iface.request_netinfo = request_netinfo;
	dev->most_iface.driver_dev = &pdev->dev;
	dev->dev.init_name = "dim2_state";
	dev->dev.parent = &dev->most_iface.dev;

	ret = most_register_interface(&dev->most_iface);
	if (ret) {
		dev_err(&pdev->dev, "failed to register MOST interface\n");
		goto err_stop_thread;
	}

	ret = dim2_sysfs_probe(&dev->dev);
	if (ret) {
		dev_err(&pdev->dev, "failed to create sysfs attribute\n");
		goto err_unreg_iface;
	}

	return 0;

err_unreg_iface:
	most_deregister_interface(&dev->most_iface);
err_stop_thread:
	kthread_stop(dev->netinfo_task);
err_shutdown_dim:
	dim_shutdown();
err_disable_platform:
	if (dev->disable_platform)
		dev->disable_platform(pdev);

	return ret;
}