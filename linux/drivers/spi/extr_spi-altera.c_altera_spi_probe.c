#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int num_chipselect; int /*<<< orphan*/  set_cs; int /*<<< orphan*/  transfer_one; TYPE_1__ dev; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  mode_bits; int /*<<< orphan*/  bus_num; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct altera_spi {scalar_t__ irq; scalar_t__ base; scalar_t__ imr; } ;

/* Variables and functions */
 scalar_t__ ALTERA_SPI_CONTROL ; 
 scalar_t__ ALTERA_SPI_RXDATA ; 
 scalar_t__ ALTERA_SPI_STATUS ; 
 int ALTERA_SPI_STATUS_RRDY_MSK ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  SPI_BPW_RANGE_MASK (int,int) ; 
 int /*<<< orphan*/  SPI_CS_HIGH ; 
 int /*<<< orphan*/  altera_spi_irq ; 
 int /*<<< orphan*/  altera_spi_set_cs ; 
 int /*<<< orphan*/  altera_spi_txrx ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_master*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct altera_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int altera_spi_probe(struct platform_device *pdev)
{
	struct altera_spi *hw;
	struct spi_master *master;
	int err = -ENODEV;

	master = spi_alloc_master(&pdev->dev, sizeof(struct altera_spi));
	if (!master)
		return err;

	/* setup the master state. */
	master->bus_num = pdev->id;
	master->num_chipselect = 16;
	master->mode_bits = SPI_CS_HIGH;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 16);
	master->dev.of_node = pdev->dev.of_node;
	master->transfer_one = altera_spi_txrx;
	master->set_cs = altera_spi_set_cs;

	hw = spi_master_get_devdata(master);

	/* find and map our resources */
	hw->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(hw->base)) {
		err = PTR_ERR(hw->base);
		goto exit;
	}
	/* program defaults into the registers */
	hw->imr = 0;		/* disable spi interrupts */
	writel(hw->imr, hw->base + ALTERA_SPI_CONTROL);
	writel(0, hw->base + ALTERA_SPI_STATUS);	/* clear status reg */
	if (readl(hw->base + ALTERA_SPI_STATUS) & ALTERA_SPI_STATUS_RRDY_MSK)
		readl(hw->base + ALTERA_SPI_RXDATA);	/* flush rxdata */
	/* irq is optional */
	hw->irq = platform_get_irq(pdev, 0);
	if (hw->irq >= 0) {
		err = devm_request_irq(&pdev->dev, hw->irq, altera_spi_irq, 0,
				       pdev->name, master);
		if (err)
			goto exit;
	}

	err = devm_spi_register_master(&pdev->dev, master);
	if (err)
		goto exit;
	dev_info(&pdev->dev, "base %p, irq %d\n", hw->base, hw->irq);

	return 0;
exit:
	spi_master_put(master);
	return err;
}