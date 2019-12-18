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
typedef  int u32 ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct spi_master {int num_chipselect; int mode_bits; int /*<<< orphan*/  bus_num; TYPE_1__ dev; int /*<<< orphan*/  set_cs; int /*<<< orphan*/  transfer_one; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct jcore_spi {int clock_freq; int /*<<< orphan*/  cs_reg; int /*<<< orphan*/  base; struct spi_master* master; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  JCORE_SPI_CTRL_CS_BITS ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_get_rate (struct clk*) ; 
 scalar_t__ clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct clk* devm_clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  jcore_spi_baudrate (struct jcore_spi*,int) ; 
 int /*<<< orphan*/  jcore_spi_chipsel ; 
 int /*<<< orphan*/  jcore_spi_txrx ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jcore_spi*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct jcore_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int jcore_spi_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct jcore_spi *hw;
	struct spi_master *master;
	struct resource *res;
	u32 clock_freq;
	struct clk *clk;
	int err = -ENODEV;

	master = spi_alloc_master(&pdev->dev, sizeof(struct jcore_spi));
	if (!master)
		return err;

	/* Setup the master state. */
	master->num_chipselect = 3;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->transfer_one = jcore_spi_txrx;
	master->set_cs = jcore_spi_chipsel;
	master->dev.of_node = node;
	master->bus_num = pdev->id;

	hw = spi_master_get_devdata(master);
	hw->master = master;
	platform_set_drvdata(pdev, hw);

	/* Find and map our resources */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		goto exit_busy;
	if (!devm_request_mem_region(&pdev->dev, res->start,
				     resource_size(res), pdev->name))
		goto exit_busy;
	hw->base = devm_ioremap_nocache(&pdev->dev, res->start,
					resource_size(res));
	if (!hw->base)
		goto exit_busy;

	/*
	 * The SPI clock rate controlled via a configurable clock divider
	 * which is applied to the reference clock. A 50 MHz reference is
	 * most suitable for obtaining standard SPI clock rates, but some
	 * designs may have a different reference clock, and the DT must
	 * make the driver aware so that it can properly program the
	 * requested rate. If the clock is omitted, 50 MHz is assumed.
	 */
	clock_freq = 50000000;
	clk = devm_clk_get(&pdev->dev, "ref_clk");
	if (!IS_ERR(clk)) {
		if (clk_prepare_enable(clk) == 0) {
			clock_freq = clk_get_rate(clk);
			clk_disable_unprepare(clk);
		} else
			dev_warn(&pdev->dev, "could not enable ref_clk\n");
	}
	hw->clock_freq = clock_freq;

	/* Initialize all CS bits to high. */
	hw->cs_reg = JCORE_SPI_CTRL_CS_BITS;
	jcore_spi_baudrate(hw, 400000);

	/* Register our spi controller */
	err = devm_spi_register_master(&pdev->dev, master);
	if (err)
		goto exit;

	return 0;

exit_busy:
	err = -EBUSY;
exit:
	spi_master_put(master);
	return err;
}