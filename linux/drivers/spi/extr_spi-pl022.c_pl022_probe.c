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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device_node* of_node; } ;
struct spi_master {int num_chipselect; int auto_runtime_pm; int mode_bits; int /*<<< orphan*/  bus_num; TYPE_1__ dev; int /*<<< orphan*/  rt; int /*<<< orphan*/  unprepare_transfer_hardware; int /*<<< orphan*/  transfer_one_message; int /*<<< orphan*/  setup; int /*<<< orphan*/  cleanup; } ;
struct pl022_ssp_controller {int num_chipselect; int* chipselects; int enable_dma; int /*<<< orphan*/  autosuspend_delay; int /*<<< orphan*/  rt; int /*<<< orphan*/  bus_id; } ;
struct pl022 {int* chipselects; int /*<<< orphan*/  clk; int /*<<< orphan*/ * virtbase; int /*<<< orphan*/  pump_transfers; int /*<<< orphan*/  phybase; TYPE_2__* vendor; struct amba_device* adev; struct pl022_ssp_controller* master_info; struct spi_master* master; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct amba_id {TYPE_2__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; } ;
struct amba_device {struct device dev; int /*<<< orphan*/ * irq; TYPE_3__ res; int /*<<< orphan*/  periphid; } ;
struct TYPE_5__ {scalar_t__ extended_cr; scalar_t__ internal_cs_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LOOP ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  SSP_CR1 (int /*<<< orphan*/ *) ; 
 int SSP_CR1_MASK_SSE ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int amba_request_regions (struct amba_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,struct pl022*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct pl022_ssp_controller* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_gpio_request (struct device*,int,char*) ; 
 int /*<<< orphan*/ * devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pl022*) ; 
 int devm_spi_register_master (struct device*,struct spi_master*) ; 
 scalar_t__ gpio_direction_output (int,int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  load_ssp_default_config (struct pl022*) ; 
 int of_get_named_gpio (struct device_node*,char*,int) ; 
 int /*<<< orphan*/  pl022_cleanup ; 
 int pl022_dma_autoprobe (struct pl022*) ; 
 int pl022_dma_probe (struct pl022*) ; 
 int /*<<< orphan*/  pl022_dma_remove (struct pl022*) ; 
 int /*<<< orphan*/  pl022_interrupt_handler ; 
 struct pl022_ssp_controller* pl022_platform_data_dt_get (struct device*) ; 
 int /*<<< orphan*/  pl022_setup ; 
 int /*<<< orphan*/  pl022_transfer_one_message ; 
 int /*<<< orphan*/  pl022_unprepare_transfer_hardware ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pump_transfers ; 
 int readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_3__*) ; 
 struct spi_master* spi_alloc_master (struct device*,int) ; 
 struct pl022* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pl022_probe(struct amba_device *adev, const struct amba_id *id)
{
	struct device *dev = &adev->dev;
	struct pl022_ssp_controller *platform_info =
			dev_get_platdata(&adev->dev);
	struct spi_master *master;
	struct pl022 *pl022 = NULL;	/*Data for this driver */
	struct device_node *np = adev->dev.of_node;
	int status = 0, i, num_cs;

	dev_info(&adev->dev,
		 "ARM PL022 driver, device ID: 0x%08x\n", adev->periphid);
	if (!platform_info && IS_ENABLED(CONFIG_OF))
		platform_info = pl022_platform_data_dt_get(dev);

	if (!platform_info) {
		dev_err(dev, "probe: no platform data defined\n");
		return -ENODEV;
	}

	if (platform_info->num_chipselect) {
		num_cs = platform_info->num_chipselect;
	} else {
		dev_err(dev, "probe: no chip select defined\n");
		return -ENODEV;
	}

	/* Allocate master with space for data */
	master = spi_alloc_master(dev, sizeof(struct pl022));
	if (master == NULL) {
		dev_err(&adev->dev, "probe - cannot alloc SPI master\n");
		return -ENOMEM;
	}

	pl022 = spi_master_get_devdata(master);
	pl022->master = master;
	pl022->master_info = platform_info;
	pl022->adev = adev;
	pl022->vendor = id->data;
	pl022->chipselects = devm_kcalloc(dev, num_cs, sizeof(int),
					  GFP_KERNEL);
	if (!pl022->chipselects) {
		status = -ENOMEM;
		goto err_no_mem;
	}

	/*
	 * Bus Number Which has been Assigned to this SSP controller
	 * on this board
	 */
	master->bus_num = platform_info->bus_id;
	master->num_chipselect = num_cs;
	master->cleanup = pl022_cleanup;
	master->setup = pl022_setup;
	master->auto_runtime_pm = true;
	master->transfer_one_message = pl022_transfer_one_message;
	master->unprepare_transfer_hardware = pl022_unprepare_transfer_hardware;
	master->rt = platform_info->rt;
	master->dev.of_node = dev->of_node;

	if (platform_info->num_chipselect && platform_info->chipselects) {
		for (i = 0; i < num_cs; i++)
			pl022->chipselects[i] = platform_info->chipselects[i];
	} else if (pl022->vendor->internal_cs_ctrl) {
		for (i = 0; i < num_cs; i++)
			pl022->chipselects[i] = i;
	} else if (IS_ENABLED(CONFIG_OF)) {
		for (i = 0; i < num_cs; i++) {
			int cs_gpio = of_get_named_gpio(np, "cs-gpios", i);

			if (cs_gpio == -EPROBE_DEFER) {
				status = -EPROBE_DEFER;
				goto err_no_gpio;
			}

			pl022->chipselects[i] = cs_gpio;

			if (gpio_is_valid(cs_gpio)) {
				if (devm_gpio_request(dev, cs_gpio, "ssp-pl022"))
					dev_err(&adev->dev,
						"could not request %d gpio\n",
						cs_gpio);
				else if (gpio_direction_output(cs_gpio, 1))
					dev_err(&adev->dev,
						"could not set gpio %d as output\n",
						cs_gpio);
			}
		}
	}

	/*
	 * Supports mode 0-3, loopback, and active low CS. Transfers are
	 * always MS bit first on the original pl022.
	 */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LOOP;
	if (pl022->vendor->extended_cr)
		master->mode_bits |= SPI_LSB_FIRST;

	dev_dbg(&adev->dev, "BUSNO: %d\n", master->bus_num);

	status = amba_request_regions(adev, NULL);
	if (status)
		goto err_no_ioregion;

	pl022->phybase = adev->res.start;
	pl022->virtbase = devm_ioremap(dev, adev->res.start,
				       resource_size(&adev->res));
	if (pl022->virtbase == NULL) {
		status = -ENOMEM;
		goto err_no_ioremap;
	}
	dev_info(&adev->dev, "mapped registers from %pa to %p\n",
		&adev->res.start, pl022->virtbase);

	pl022->clk = devm_clk_get(&adev->dev, NULL);
	if (IS_ERR(pl022->clk)) {
		status = PTR_ERR(pl022->clk);
		dev_err(&adev->dev, "could not retrieve SSP/SPI bus clock\n");
		goto err_no_clk;
	}

	status = clk_prepare_enable(pl022->clk);
	if (status) {
		dev_err(&adev->dev, "could not enable SSP/SPI bus clock\n");
		goto err_no_clk_en;
	}

	/* Initialize transfer pump */
	tasklet_init(&pl022->pump_transfers, pump_transfers,
		     (unsigned long)pl022);

	/* Disable SSP */
	writew((readw(SSP_CR1(pl022->virtbase)) & (~SSP_CR1_MASK_SSE)),
	       SSP_CR1(pl022->virtbase));
	load_ssp_default_config(pl022);

	status = devm_request_irq(dev, adev->irq[0], pl022_interrupt_handler,
				  0, "pl022", pl022);
	if (status < 0) {
		dev_err(&adev->dev, "probe - cannot get IRQ (%d)\n", status);
		goto err_no_irq;
	}

	/* Get DMA channels, try autoconfiguration first */
	status = pl022_dma_autoprobe(pl022);
	if (status == -EPROBE_DEFER) {
		dev_dbg(dev, "deferring probe to get DMA channel\n");
		goto err_no_irq;
	}

	/* If that failed, use channels from platform_info */
	if (status == 0)
		platform_info->enable_dma = 1;
	else if (platform_info->enable_dma) {
		status = pl022_dma_probe(pl022);
		if (status != 0)
			platform_info->enable_dma = 0;
	}

	/* Register with the SPI framework */
	amba_set_drvdata(adev, pl022);
	status = devm_spi_register_master(&adev->dev, master);
	if (status != 0) {
		dev_err(&adev->dev,
			"probe - problem registering spi master\n");
		goto err_spi_register;
	}
	dev_dbg(dev, "probe succeeded\n");

	/* let runtime pm put suspend */
	if (platform_info->autosuspend_delay > 0) {
		dev_info(&adev->dev,
			"will use autosuspend for runtime pm, delay %dms\n",
			platform_info->autosuspend_delay);
		pm_runtime_set_autosuspend_delay(dev,
			platform_info->autosuspend_delay);
		pm_runtime_use_autosuspend(dev);
	}
	pm_runtime_put(dev);

	return 0;

 err_spi_register:
	if (platform_info->enable_dma)
		pl022_dma_remove(pl022);
 err_no_irq:
	clk_disable_unprepare(pl022->clk);
 err_no_clk_en:
 err_no_clk:
 err_no_ioremap:
	amba_release_regions(adev);
 err_no_ioregion:
 err_no_gpio:
 err_no_mem:
	spi_master_put(master);
	return status;
}