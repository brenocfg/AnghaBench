#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  virt; } ;
struct aspeed_video {void* eclk; void* vclk; int /*<<< orphan*/  yuv420; TYPE_1__ jpeg; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  VE_JPEG_HEADER_SIZE ; 
 int /*<<< orphan*/  aspeed_video_alloc_buf (struct aspeed_video*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_video_init_jpeg_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_video_irq ; 
 int clk_prepare (void*) ; 
 int /*<<< orphan*/  clk_unprepare (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aspeed_video*) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_reserved_mem_device_init (struct device*) ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (struct device*) ; 

__attribute__((used)) static int aspeed_video_init(struct aspeed_video *video)
{
	int irq;
	int rc;
	struct device *dev = video->dev;

	irq = irq_of_parse_and_map(dev->of_node, 0);
	if (!irq) {
		dev_err(dev, "Unable to find IRQ\n");
		return -ENODEV;
	}

	rc = devm_request_threaded_irq(dev, irq, NULL, aspeed_video_irq,
				       IRQF_ONESHOT, DEVICE_NAME, video);
	if (rc < 0) {
		dev_err(dev, "Unable to request IRQ %d\n", irq);
		return rc;
	}

	video->eclk = devm_clk_get(dev, "eclk");
	if (IS_ERR(video->eclk)) {
		dev_err(dev, "Unable to get ECLK\n");
		return PTR_ERR(video->eclk);
	}

	rc = clk_prepare(video->eclk);
	if (rc)
		return rc;

	video->vclk = devm_clk_get(dev, "vclk");
	if (IS_ERR(video->vclk)) {
		dev_err(dev, "Unable to get VCLK\n");
		rc = PTR_ERR(video->vclk);
		goto err_unprepare_eclk;
	}

	rc = clk_prepare(video->vclk);
	if (rc)
		goto err_unprepare_eclk;

	of_reserved_mem_device_init(dev);

	rc = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	if (rc) {
		dev_err(dev, "Failed to set DMA mask\n");
		goto err_release_reserved_mem;
	}

	if (!aspeed_video_alloc_buf(video, &video->jpeg,
				    VE_JPEG_HEADER_SIZE)) {
		dev_err(dev, "Failed to allocate DMA for JPEG header\n");
		rc = -ENOMEM;
		goto err_release_reserved_mem;
	}

	aspeed_video_init_jpeg_table(video->jpeg.virt, video->yuv420);

	return 0;

err_release_reserved_mem:
	of_reserved_mem_device_release(dev);
	clk_unprepare(video->vclk);
err_unprepare_eclk:
	clk_unprepare(video->eclk);

	return rc;
}