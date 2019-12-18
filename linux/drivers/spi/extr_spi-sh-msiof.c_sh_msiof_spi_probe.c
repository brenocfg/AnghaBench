#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  of_node; } ;
struct spi_controller {int mode_bits; int auto_runtime_pm; int use_gpio_descriptors; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  slave_abort; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  setup; TYPE_2__ dev; int /*<<< orphan*/  bus_num; int /*<<< orphan*/  flags; int /*<<< orphan*/  num_chipselect; } ;
struct sh_msiof_spi_priv {struct sh_msiof_spi_info* info; scalar_t__ rx_fifo_size; scalar_t__ tx_fifo_size; struct platform_device* pdev; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  clk; int /*<<< orphan*/  done_txdma; int /*<<< orphan*/  done; int /*<<< orphan*/  min_div_pow; struct spi_controller* ctlr; } ;
struct sh_msiof_spi_info {scalar_t__ mode; int /*<<< orphan*/  num_chipselect; scalar_t__ rx_fifo_override; scalar_t__ tx_fifo_override; } ;
struct sh_msiof_chipdata {int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  ctlr_flags; scalar_t__ rx_fifo_size; scalar_t__ tx_fifo_size; int /*<<< orphan*/  min_div_pow; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  id; TYPE_1__* id_entry; } ;
struct TYPE_16__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MSIOF_SPI_SLAVE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_3WIRE ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct sh_msiof_spi_info* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sh_msiof_spi_priv*) ; 
 int devm_spi_register_controller (TYPE_3__*,struct spi_controller*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct sh_msiof_chipdata* of_device_get_match_data (TYPE_3__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_msiof_spi_priv*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int sh_msiof_get_cs_gpios (struct sh_msiof_spi_priv*) ; 
 int /*<<< orphan*/  sh_msiof_prepare_message ; 
 int /*<<< orphan*/  sh_msiof_release_dma (struct sh_msiof_spi_priv*) ; 
 int sh_msiof_request_dma (struct sh_msiof_spi_priv*) ; 
 int /*<<< orphan*/  sh_msiof_slave_abort ; 
 int /*<<< orphan*/  sh_msiof_spi_irq ; 
 struct sh_msiof_spi_info* sh_msiof_spi_parse_dt (TYPE_3__*) ; 
 int /*<<< orphan*/  sh_msiof_spi_setup ; 
 int /*<<< orphan*/  sh_msiof_transfer_one ; 
 struct spi_controller* spi_alloc_master (TYPE_3__*,int) ; 
 struct spi_controller* spi_alloc_slave (TYPE_3__*,int) ; 
 struct sh_msiof_spi_priv* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_controller_put (struct spi_controller*) ; 

__attribute__((used)) static int sh_msiof_spi_probe(struct platform_device *pdev)
{
	struct spi_controller *ctlr;
	const struct sh_msiof_chipdata *chipdata;
	struct sh_msiof_spi_info *info;
	struct sh_msiof_spi_priv *p;
	int i;
	int ret;

	chipdata = of_device_get_match_data(&pdev->dev);
	if (chipdata) {
		info = sh_msiof_spi_parse_dt(&pdev->dev);
	} else {
		chipdata = (const void *)pdev->id_entry->driver_data;
		info = dev_get_platdata(&pdev->dev);
	}

	if (!info) {
		dev_err(&pdev->dev, "failed to obtain device info\n");
		return -ENXIO;
	}

	if (info->mode == MSIOF_SPI_SLAVE)
		ctlr = spi_alloc_slave(&pdev->dev,
				       sizeof(struct sh_msiof_spi_priv));
	else
		ctlr = spi_alloc_master(&pdev->dev,
					sizeof(struct sh_msiof_spi_priv));
	if (ctlr == NULL)
		return -ENOMEM;

	p = spi_controller_get_devdata(ctlr);

	platform_set_drvdata(pdev, p);
	p->ctlr = ctlr;
	p->info = info;
	p->min_div_pow = chipdata->min_div_pow;

	init_completion(&p->done);
	init_completion(&p->done_txdma);

	p->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(p->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		ret = PTR_ERR(p->clk);
		goto err1;
	}

	i = platform_get_irq(pdev, 0);
	if (i < 0) {
		ret = i;
		goto err1;
	}

	p->mapbase = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(p->mapbase)) {
		ret = PTR_ERR(p->mapbase);
		goto err1;
	}

	ret = devm_request_irq(&pdev->dev, i, sh_msiof_spi_irq, 0,
			       dev_name(&pdev->dev), p);
	if (ret) {
		dev_err(&pdev->dev, "unable to request irq\n");
		goto err1;
	}

	p->pdev = pdev;
	pm_runtime_enable(&pdev->dev);

	/* Platform data may override FIFO sizes */
	p->tx_fifo_size = chipdata->tx_fifo_size;
	p->rx_fifo_size = chipdata->rx_fifo_size;
	if (p->info->tx_fifo_override)
		p->tx_fifo_size = p->info->tx_fifo_override;
	if (p->info->rx_fifo_override)
		p->rx_fifo_size = p->info->rx_fifo_override;

	/* Setup GPIO chip selects */
	ctlr->num_chipselect = p->info->num_chipselect;
	ret = sh_msiof_get_cs_gpios(p);
	if (ret)
		goto err1;

	/* init controller code */
	ctlr->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	ctlr->mode_bits |= SPI_LSB_FIRST | SPI_3WIRE;
	ctlr->flags = chipdata->ctlr_flags;
	ctlr->bus_num = pdev->id;
	ctlr->dev.of_node = pdev->dev.of_node;
	ctlr->setup = sh_msiof_spi_setup;
	ctlr->prepare_message = sh_msiof_prepare_message;
	ctlr->slave_abort = sh_msiof_slave_abort;
	ctlr->bits_per_word_mask = chipdata->bits_per_word_mask;
	ctlr->auto_runtime_pm = true;
	ctlr->transfer_one = sh_msiof_transfer_one;
	ctlr->use_gpio_descriptors = true;

	ret = sh_msiof_request_dma(p);
	if (ret < 0)
		dev_warn(&pdev->dev, "DMA not available, using PIO\n");

	ret = devm_spi_register_controller(&pdev->dev, ctlr);
	if (ret < 0) {
		dev_err(&pdev->dev, "devm_spi_register_controller error.\n");
		goto err2;
	}

	return 0;

 err2:
	sh_msiof_release_dma(p);
	pm_runtime_disable(&pdev->dev);
 err1:
	spi_controller_put(ctlr);
	return ret;
}