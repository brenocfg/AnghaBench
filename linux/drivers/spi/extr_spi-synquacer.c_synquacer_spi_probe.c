#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct synquacer_spi {void* clk; TYPE_2__* dev; int /*<<< orphan*/  tx_irq_name; int /*<<< orphan*/  rx_irq_name; void* rtm; void* aces; void* clk_src_type; void* regs; int /*<<< orphan*/  transfer_done; } ;
struct TYPE_15__ {int /*<<< orphan*/  fwnode; struct device_node* of_node; } ;
struct spi_master {int max_speed_hz; int min_speed_hz; int auto_runtime_pm; int mode_bits; int bits_per_word_mask; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  set_cs; int /*<<< orphan*/  bus_num; TYPE_1__ dev; int /*<<< orphan*/  num_chipselect; } ;
struct TYPE_16__ {int /*<<< orphan*/  fwnode; struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_2__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 void* SYNQUACER_HSSPI_CLOCK_SRC_IHCLK ; 
 void* SYNQUACER_HSSPI_CLOCK_SRC_IPCLK ; 
 int /*<<< orphan*/  SYNQUACER_HSSPI_IRQ_NAME_MAX ; 
 int /*<<< orphan*/  SYNQUACER_HSSPI_NUM_CHIP_SELECT ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 char* dev_name (TYPE_2__*) ; 
 scalar_t__ dev_of_node (TYPE_2__*) ; 
 scalar_t__ device_property_match_string (TYPE_2__*,char*,char*) ; 
 void* device_property_read_bool (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (TYPE_2__*,char*,int*) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct synquacer_spi*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct synquacer_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  sq_spi_rx_handler ; 
 int /*<<< orphan*/  sq_spi_tx_handler ; 
 int synquacer_spi_enable (struct spi_master*) ; 
 int /*<<< orphan*/  synquacer_spi_set_cs ; 
 int /*<<< orphan*/  synquacer_spi_transfer_one ; 

__attribute__((used)) static int synquacer_spi_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct spi_master *master;
	struct synquacer_spi *sspi;
	int ret;
	int rx_irq, tx_irq;

	master = spi_alloc_master(&pdev->dev, sizeof(*sspi));
	if (!master)
		return -ENOMEM;

	platform_set_drvdata(pdev, master);

	sspi = spi_master_get_devdata(master);
	sspi->dev = &pdev->dev;

	init_completion(&sspi->transfer_done);

	sspi->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(sspi->regs)) {
		ret = PTR_ERR(sspi->regs);
		goto put_spi;
	}

	sspi->clk_src_type = SYNQUACER_HSSPI_CLOCK_SRC_IHCLK; /* Default */
	device_property_read_u32(&pdev->dev, "socionext,ihclk-rate",
				 &master->max_speed_hz); /* for ACPI */

	if (dev_of_node(&pdev->dev)) {
		if (device_property_match_string(&pdev->dev,
					 "clock-names", "iHCLK") >= 0) {
			sspi->clk_src_type = SYNQUACER_HSSPI_CLOCK_SRC_IHCLK;
			sspi->clk = devm_clk_get(sspi->dev, "iHCLK");
		} else if (device_property_match_string(&pdev->dev,
						"clock-names", "iPCLK") >= 0) {
			sspi->clk_src_type = SYNQUACER_HSSPI_CLOCK_SRC_IPCLK;
			sspi->clk = devm_clk_get(sspi->dev, "iPCLK");
		} else {
			dev_err(&pdev->dev, "specified wrong clock source\n");
			ret = -EINVAL;
			goto put_spi;
		}

		if (IS_ERR(sspi->clk)) {
			if (!(PTR_ERR(sspi->clk) == -EPROBE_DEFER))
				dev_err(&pdev->dev, "clock not found\n");
			ret = PTR_ERR(sspi->clk);
			goto put_spi;
		}

		ret = clk_prepare_enable(sspi->clk);
		if (ret) {
			dev_err(&pdev->dev, "failed to enable clock (%d)\n",
				ret);
			goto put_spi;
		}

		master->max_speed_hz = clk_get_rate(sspi->clk);
	}

	if (!master->max_speed_hz) {
		dev_err(&pdev->dev, "missing clock source\n");
		return -EINVAL;
	}
	master->min_speed_hz = master->max_speed_hz / 254;

	sspi->aces = device_property_read_bool(&pdev->dev,
					       "socionext,set-aces");
	sspi->rtm = device_property_read_bool(&pdev->dev, "socionext,use-rtm");

	master->num_chipselect = SYNQUACER_HSSPI_NUM_CHIP_SELECT;

	rx_irq = platform_get_irq(pdev, 0);
	if (rx_irq <= 0) {
		ret = rx_irq;
		goto put_spi;
	}
	snprintf(sspi->rx_irq_name, SYNQUACER_HSSPI_IRQ_NAME_MAX, "%s-rx",
		 dev_name(&pdev->dev));
	ret = devm_request_irq(&pdev->dev, rx_irq, sq_spi_rx_handler,
				0, sspi->rx_irq_name, sspi);
	if (ret) {
		dev_err(&pdev->dev, "request rx_irq failed (%d)\n", ret);
		goto put_spi;
	}

	tx_irq = platform_get_irq(pdev, 1);
	if (tx_irq <= 0) {
		ret = tx_irq;
		goto put_spi;
	}
	snprintf(sspi->tx_irq_name, SYNQUACER_HSSPI_IRQ_NAME_MAX, "%s-tx",
		 dev_name(&pdev->dev));
	ret = devm_request_irq(&pdev->dev, tx_irq, sq_spi_tx_handler,
				0, sspi->tx_irq_name, sspi);
	if (ret) {
		dev_err(&pdev->dev, "request tx_irq failed (%d)\n", ret);
		goto put_spi;
	}

	master->dev.of_node = np;
	master->dev.fwnode = pdev->dev.fwnode;
	master->auto_runtime_pm = true;
	master->bus_num = pdev->id;

	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_TX_DUAL | SPI_RX_DUAL |
			    SPI_TX_QUAD | SPI_RX_QUAD;
	master->bits_per_word_mask = SPI_BPW_MASK(32) | SPI_BPW_MASK(24) |
				     SPI_BPW_MASK(16) | SPI_BPW_MASK(8);

	master->set_cs = synquacer_spi_set_cs;
	master->transfer_one = synquacer_spi_transfer_one;

	ret = synquacer_spi_enable(master);
	if (ret)
		goto fail_enable;

	pm_runtime_set_active(sspi->dev);
	pm_runtime_enable(sspi->dev);

	ret = devm_spi_register_master(sspi->dev, master);
	if (ret)
		goto disable_pm;

	return 0;

disable_pm:
	pm_runtime_disable(sspi->dev);
fail_enable:
	clk_disable_unprepare(sspi->clk);
put_spi:
	spi_master_put(master);

	return ret;
}