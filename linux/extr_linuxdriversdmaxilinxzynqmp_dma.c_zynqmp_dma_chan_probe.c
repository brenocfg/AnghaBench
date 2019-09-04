#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_7__ {int /*<<< orphan*/  channels; } ;
struct zynqmp_dma_device {TYPE_1__ common; struct zynqmp_dma_chan* chan; TYPE_3__* dev; } ;
struct zynqmp_dma_desc_ll {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  device_node; TYPE_1__* device; } ;
struct zynqmp_dma_chan {scalar_t__ bus_width; scalar_t__ irq; int desc_size; int idle; TYPE_2__ common; int /*<<< orphan*/  free_list; int /*<<< orphan*/  done_list; int /*<<< orphan*/  pending_list; int /*<<< orphan*/  active_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  is_dmacoherent; int /*<<< orphan*/  src_burst_len; int /*<<< orphan*/  dst_burst_len; int /*<<< orphan*/  regs; struct zynqmp_dma_device* zdev; TYPE_3__* dev; } ;
struct resource {int dummy; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZYNQMP_DMA_ARLEN_RST_VAL ; 
 int /*<<< orphan*/  ZYNQMP_DMA_AWLEN_RST_VAL ; 
 scalar_t__ ZYNQMP_DMA_BUS_WIDTH_128 ; 
 scalar_t__ ZYNQMP_DMA_BUS_WIDTH_64 ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct zynqmp_dma_chan* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct zynqmp_dma_chan*) ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_dma_do_tasklet ; 
 int /*<<< orphan*/  zynqmp_dma_init (struct zynqmp_dma_chan*) ; 
 int /*<<< orphan*/  zynqmp_dma_irq_handler ; 

__attribute__((used)) static int zynqmp_dma_chan_probe(struct zynqmp_dma_device *zdev,
			   struct platform_device *pdev)
{
	struct zynqmp_dma_chan *chan;
	struct resource *res;
	struct device_node *node = pdev->dev.of_node;
	int err;

	chan = devm_kzalloc(zdev->dev, sizeof(*chan), GFP_KERNEL);
	if (!chan)
		return -ENOMEM;
	chan->dev = zdev->dev;
	chan->zdev = zdev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	chan->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(chan->regs))
		return PTR_ERR(chan->regs);

	chan->bus_width = ZYNQMP_DMA_BUS_WIDTH_64;
	chan->dst_burst_len = ZYNQMP_DMA_AWLEN_RST_VAL;
	chan->src_burst_len = ZYNQMP_DMA_ARLEN_RST_VAL;
	err = of_property_read_u32(node, "xlnx,bus-width", &chan->bus_width);
	if (err < 0) {
		dev_err(&pdev->dev, "missing xlnx,bus-width property\n");
		return err;
	}

	if (chan->bus_width != ZYNQMP_DMA_BUS_WIDTH_64 &&
	    chan->bus_width != ZYNQMP_DMA_BUS_WIDTH_128) {
		dev_err(zdev->dev, "invalid bus-width value");
		return -EINVAL;
	}

	chan->is_dmacoherent =  of_property_read_bool(node, "dma-coherent");
	zdev->chan = chan;
	tasklet_init(&chan->tasklet, zynqmp_dma_do_tasklet, (ulong)chan);
	spin_lock_init(&chan->lock);
	INIT_LIST_HEAD(&chan->active_list);
	INIT_LIST_HEAD(&chan->pending_list);
	INIT_LIST_HEAD(&chan->done_list);
	INIT_LIST_HEAD(&chan->free_list);

	dma_cookie_init(&chan->common);
	chan->common.device = &zdev->common;
	list_add_tail(&chan->common.device_node, &zdev->common.channels);

	zynqmp_dma_init(chan);
	chan->irq = platform_get_irq(pdev, 0);
	if (chan->irq < 0)
		return -ENXIO;
	err = devm_request_irq(&pdev->dev, chan->irq, zynqmp_dma_irq_handler, 0,
			       "zynqmp-dma", chan);
	if (err)
		return err;

	chan->desc_size = sizeof(struct zynqmp_dma_desc_ll);
	chan->idle = true;
	return 0;
}