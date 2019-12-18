#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int auto_runtime_pm; int mode_bits; int bits_per_word_mask; int max_speed_hz; int min_speed_hz; int /*<<< orphan*/  can_dma; void* dma_rx; void* dma_tx; int /*<<< orphan*/  handle_err; int /*<<< orphan*/  unprepare_message; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  setup; TYPE_1__ dev; int /*<<< orphan*/  bus_num; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_14__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; } ;
struct img_spfi {int irq; void* sys_clk; void* spfi_clk; void* tx_ch; void* rx_ch; TYPE_2__* dev; int /*<<< orphan*/  phys; void* regs; int /*<<< orphan*/  lock; struct spi_master* master; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQ_TYPE_LEVEL_HIGH ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SPFI_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SPFI_INTERRUPT_IACCESS ; 
 int SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 void* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct img_spfi*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 
 void* dma_request_slave_channel (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  img_spfi_can_dma ; 
 int /*<<< orphan*/  img_spfi_cleanup ; 
 int /*<<< orphan*/  img_spfi_handle_err ; 
 int /*<<< orphan*/  img_spfi_irq ; 
 int /*<<< orphan*/  img_spfi_prepare ; 
 int /*<<< orphan*/  img_spfi_setup ; 
 int /*<<< orphan*/  img_spfi_transfer_one ; 
 int /*<<< orphan*/  img_spfi_unprepare ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  spfi_reset (struct img_spfi*) ; 
 int /*<<< orphan*/  spfi_writel (struct img_spfi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct img_spfi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int img_spfi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct img_spfi *spfi;
	struct resource *res;
	int ret;
	u32 max_speed_hz;

	master = spi_alloc_master(&pdev->dev, sizeof(*spfi));
	if (!master)
		return -ENOMEM;
	platform_set_drvdata(pdev, master);

	spfi = spi_master_get_devdata(master);
	spfi->dev = &pdev->dev;
	spfi->master = master;
	spin_lock_init(&spfi->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	spfi->regs = devm_ioremap_resource(spfi->dev, res);
	if (IS_ERR(spfi->regs)) {
		ret = PTR_ERR(spfi->regs);
		goto put_spi;
	}
	spfi->phys = res->start;

	spfi->irq = platform_get_irq(pdev, 0);
	if (spfi->irq < 0) {
		ret = spfi->irq;
		goto put_spi;
	}
	ret = devm_request_irq(spfi->dev, spfi->irq, img_spfi_irq,
			       IRQ_TYPE_LEVEL_HIGH, dev_name(spfi->dev), spfi);
	if (ret)
		goto put_spi;

	spfi->sys_clk = devm_clk_get(spfi->dev, "sys");
	if (IS_ERR(spfi->sys_clk)) {
		ret = PTR_ERR(spfi->sys_clk);
		goto put_spi;
	}
	spfi->spfi_clk = devm_clk_get(spfi->dev, "spfi");
	if (IS_ERR(spfi->spfi_clk)) {
		ret = PTR_ERR(spfi->spfi_clk);
		goto put_spi;
	}

	ret = clk_prepare_enable(spfi->sys_clk);
	if (ret)
		goto put_spi;
	ret = clk_prepare_enable(spfi->spfi_clk);
	if (ret)
		goto disable_pclk;

	spfi_reset(spfi);
	/*
	 * Only enable the error (IACCESS) interrupt.  In PIO mode we'll
	 * poll the status of the FIFOs.
	 */
	spfi_writel(spfi, SPFI_INTERRUPT_IACCESS, SPFI_INTERRUPT_ENABLE);

	master->auto_runtime_pm = true;
	master->bus_num = pdev->id;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_TX_DUAL | SPI_RX_DUAL;
	if (of_property_read_bool(spfi->dev->of_node, "img,supports-quad-mode"))
		master->mode_bits |= SPI_TX_QUAD | SPI_RX_QUAD;
	master->dev.of_node = pdev->dev.of_node;
	master->bits_per_word_mask = SPI_BPW_MASK(32) | SPI_BPW_MASK(8);
	master->max_speed_hz = clk_get_rate(spfi->spfi_clk) / 4;
	master->min_speed_hz = clk_get_rate(spfi->spfi_clk) / 512;

	/*
	 * Maximum speed supported by spfi is limited to the lower value
	 * between 1/4 of the SPFI clock or to "spfi-max-frequency"
	 * defined in the device tree.
	 * If no value is defined in the device tree assume the maximum
	 * speed supported to be 1/4 of the SPFI clock.
	 */
	if (!of_property_read_u32(spfi->dev->of_node, "spfi-max-frequency",
				  &max_speed_hz)) {
		if (master->max_speed_hz > max_speed_hz)
			master->max_speed_hz = max_speed_hz;
	}

	master->setup = img_spfi_setup;
	master->cleanup = img_spfi_cleanup;
	master->transfer_one = img_spfi_transfer_one;
	master->prepare_message = img_spfi_prepare;
	master->unprepare_message = img_spfi_unprepare;
	master->handle_err = img_spfi_handle_err;

	spfi->tx_ch = dma_request_slave_channel(spfi->dev, "tx");
	spfi->rx_ch = dma_request_slave_channel(spfi->dev, "rx");
	if (!spfi->tx_ch || !spfi->rx_ch) {
		if (spfi->tx_ch)
			dma_release_channel(spfi->tx_ch);
		if (spfi->rx_ch)
			dma_release_channel(spfi->rx_ch);
		dev_warn(spfi->dev, "Failed to get DMA channels, falling back to PIO mode\n");
	} else {
		master->dma_tx = spfi->tx_ch;
		master->dma_rx = spfi->rx_ch;
		master->can_dma = img_spfi_can_dma;
	}

	pm_runtime_set_active(spfi->dev);
	pm_runtime_enable(spfi->dev);

	ret = devm_spi_register_master(spfi->dev, master);
	if (ret)
		goto disable_pm;

	return 0;

disable_pm:
	pm_runtime_disable(spfi->dev);
	if (spfi->rx_ch)
		dma_release_channel(spfi->rx_ch);
	if (spfi->tx_ch)
		dma_release_channel(spfi->tx_ch);
	clk_disable_unprepare(spfi->spfi_clk);
disable_pclk:
	clk_disable_unprepare(spfi->sys_clk);
put_spi:
	spi_master_put(master);

	return ret;
}