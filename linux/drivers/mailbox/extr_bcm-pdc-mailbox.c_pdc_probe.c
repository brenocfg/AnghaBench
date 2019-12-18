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
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct pdc_state {int /*<<< orphan*/  ring_pool; int /*<<< orphan*/  rx_buf_pool; int /*<<< orphan*/  rx_tasklet; int /*<<< orphan*/  pdc_reg_vbase; int /*<<< orphan*/  pdc_idx; struct platform_device* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_spu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDC_RING_SIZE ; 
 int PDC_SUCCESS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_ALIGN ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct pdc_state* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_create (char*,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int pdc_dt_read (struct platform_device*,struct pdc_state*) ; 
 int /*<<< orphan*/  pdc_hw_init (struct pdc_state*) ; 
 int pdc_interrupts_init (struct pdc_state*) ; 
 int pdc_mb_init (struct pdc_state*) ; 
 int pdc_rx_buf_pool_create (struct pdc_state*) ; 
 int /*<<< orphan*/  pdc_setup_debugfs (struct pdc_state*) ; 
 int /*<<< orphan*/  pdc_tasklet_cb ; 
 TYPE_1__ pdcg ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pdc_state*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdc_probe(struct platform_device *pdev)
{
	int err = 0;
	struct device *dev = &pdev->dev;
	struct resource *pdc_regs;
	struct pdc_state *pdcs;

	/* PDC state for one SPU */
	pdcs = devm_kzalloc(dev, sizeof(*pdcs), GFP_KERNEL);
	if (!pdcs) {
		err = -ENOMEM;
		goto cleanup;
	}

	pdcs->pdev = pdev;
	platform_set_drvdata(pdev, pdcs);
	pdcs->pdc_idx = pdcg.num_spu;
	pdcg.num_spu++;

	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(39));
	if (err) {
		dev_warn(dev, "PDC device cannot perform DMA. Error %d.", err);
		goto cleanup;
	}

	/* Create DMA pool for tx ring */
	pdcs->ring_pool = dma_pool_create("pdc rings", dev, PDC_RING_SIZE,
					  RING_ALIGN, 0);
	if (!pdcs->ring_pool) {
		err = -ENOMEM;
		goto cleanup;
	}

	err = pdc_dt_read(pdev, pdcs);
	if (err)
		goto cleanup_ring_pool;

	pdc_regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!pdc_regs) {
		err = -ENODEV;
		goto cleanup_ring_pool;
	}
	dev_dbg(dev, "PDC register region res.start = %pa, res.end = %pa",
		&pdc_regs->start, &pdc_regs->end);

	pdcs->pdc_reg_vbase = devm_ioremap_resource(&pdev->dev, pdc_regs);
	if (IS_ERR(pdcs->pdc_reg_vbase)) {
		err = PTR_ERR(pdcs->pdc_reg_vbase);
		dev_err(&pdev->dev, "Failed to map registers: %d\n", err);
		goto cleanup_ring_pool;
	}

	/* create rx buffer pool after dt read to know how big buffers are */
	err = pdc_rx_buf_pool_create(pdcs);
	if (err)
		goto cleanup_ring_pool;

	pdc_hw_init(pdcs);

	/* Init tasklet for deferred DMA rx processing */
	tasklet_init(&pdcs->rx_tasklet, pdc_tasklet_cb, (unsigned long)pdcs);

	err = pdc_interrupts_init(pdcs);
	if (err)
		goto cleanup_buf_pool;

	/* Initialize mailbox controller */
	err = pdc_mb_init(pdcs);
	if (err)
		goto cleanup_buf_pool;

	pdc_setup_debugfs(pdcs);

	dev_dbg(dev, "pdc_probe() successful");
	return PDC_SUCCESS;

cleanup_buf_pool:
	tasklet_kill(&pdcs->rx_tasklet);
	dma_pool_destroy(pdcs->rx_buf_pool);

cleanup_ring_pool:
	dma_pool_destroy(pdcs->ring_pool);

cleanup:
	return err;
}