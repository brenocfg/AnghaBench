#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int auto_runtime_pm; int num_chipselect; int mode_bits; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  set_cs; int /*<<< orphan*/ * mem_ops; TYPE_1__ dev; } ;
struct resource {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mxic_spi {void* regs; void* send_dly_clk; void* send_clk; void* ps_clk; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 void* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  mxic_spi_hw_init (struct mxic_spi*) ; 
 int /*<<< orphan*/  mxic_spi_mem_ops ; 
 int /*<<< orphan*/  mxic_spi_set_cs ; 
 int /*<<< orphan*/  mxic_spi_transfer_one ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct mxic_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int spi_register_master (struct spi_master*) ; 

__attribute__((used)) static int mxic_spi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct resource *res;
	struct mxic_spi *mxic;
	int ret;

	master = spi_alloc_master(&pdev->dev, sizeof(struct mxic_spi));
	if (!master)
		return -ENOMEM;

	platform_set_drvdata(pdev, master);

	mxic = spi_master_get_devdata(master);

	master->dev.of_node = pdev->dev.of_node;

	mxic->ps_clk = devm_clk_get(&pdev->dev, "ps_clk");
	if (IS_ERR(mxic->ps_clk))
		return PTR_ERR(mxic->ps_clk);

	mxic->send_clk = devm_clk_get(&pdev->dev, "send_clk");
	if (IS_ERR(mxic->send_clk))
		return PTR_ERR(mxic->send_clk);

	mxic->send_dly_clk = devm_clk_get(&pdev->dev, "send_dly_clk");
	if (IS_ERR(mxic->send_dly_clk))
		return PTR_ERR(mxic->send_dly_clk);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "regs");
	mxic->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mxic->regs))
		return PTR_ERR(mxic->regs);

	pm_runtime_enable(&pdev->dev);
	master->auto_runtime_pm = true;

	master->num_chipselect = 1;
	master->mem_ops = &mxic_spi_mem_ops;

	master->set_cs = mxic_spi_set_cs;
	master->transfer_one = mxic_spi_transfer_one;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->mode_bits = SPI_CPOL | SPI_CPHA |
			SPI_RX_DUAL | SPI_TX_DUAL |
			SPI_RX_QUAD | SPI_TX_QUAD;

	mxic_spi_hw_init(mxic);

	ret = spi_register_master(master);
	if (ret) {
		dev_err(&pdev->dev, "spi_register_master failed\n");
		goto err_put_master;
	}

	return 0;

err_put_master:
	spi_master_put(master);
	pm_runtime_disable(&pdev->dev);

	return ret;
}