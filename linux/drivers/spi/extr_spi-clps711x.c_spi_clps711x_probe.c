#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int use_gpio_descriptors; int bus_num; int mode_bits; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  prepare_message; TYPE_1__ dev; int /*<<< orphan*/  bits_per_word_mask; } ;
struct spi_clps711x_data {int /*<<< orphan*/  syncio; int /*<<< orphan*/  syscon; int /*<<< orphan*/  spi_clk; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_BPW_RANGE_MASK (int,int) ; 
 int SPI_CPHA ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  SYSCON3_ADCCON ; 
 int /*<<< orphan*/  SYSCON_OFFSET ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_master*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 int /*<<< orphan*/  spi_clps711x_isr ; 
 int /*<<< orphan*/  spi_clps711x_prepare_message ; 
 int /*<<< orphan*/  spi_clps711x_transfer_one ; 
 struct spi_clps711x_data* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static int spi_clps711x_probe(struct platform_device *pdev)
{
	struct spi_clps711x_data *hw;
	struct spi_master *master;
	int irq, ret;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	master = spi_alloc_master(&pdev->dev, sizeof(*hw));
	if (!master)
		return -ENOMEM;

	master->use_gpio_descriptors = true;
	master->bus_num = -1;
	master->mode_bits = SPI_CPHA | SPI_CS_HIGH;
	master->bits_per_word_mask =  SPI_BPW_RANGE_MASK(1, 8);
	master->dev.of_node = pdev->dev.of_node;
	master->prepare_message = spi_clps711x_prepare_message;
	master->transfer_one = spi_clps711x_transfer_one;

	hw = spi_master_get_devdata(master);

	hw->spi_clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(hw->spi_clk)) {
		ret = PTR_ERR(hw->spi_clk);
		goto err_out;
	}

	hw->syscon =
		syscon_regmap_lookup_by_compatible("cirrus,ep7209-syscon3");
	if (IS_ERR(hw->syscon)) {
		ret = PTR_ERR(hw->syscon);
		goto err_out;
	}

	hw->syncio = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(hw->syncio)) {
		ret = PTR_ERR(hw->syncio);
		goto err_out;
	}

	/* Disable extended mode due hardware problems */
	regmap_update_bits(hw->syscon, SYSCON_OFFSET, SYSCON3_ADCCON, 0);

	/* Clear possible pending interrupt */
	readl(hw->syncio);

	ret = devm_request_irq(&pdev->dev, irq, spi_clps711x_isr, 0,
			       dev_name(&pdev->dev), master);
	if (ret)
		goto err_out;

	ret = devm_spi_register_master(&pdev->dev, master);
	if (!ret)
		return 0;

err_out:
	spi_master_put(master);

	return ret;
}