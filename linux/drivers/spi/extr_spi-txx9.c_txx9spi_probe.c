#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct txx9spi {int baseclk; int last_chipselect; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * membase; int /*<<< orphan*/  waitq; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; } ;
struct spi_master {int max_speed_hz; int mode_bits; int bits_per_word_mask; scalar_t__ num_chipselect; int /*<<< orphan*/  transfer; int /*<<< orphan*/  setup; int /*<<< orphan*/  bus_num; int /*<<< orphan*/  min_speed_hz; } ;
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,scalar_t__) ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 scalar_t__ SPI_MAX_DIVIDER ; 
 int SPI_MIN_DIVIDER ; 
 int /*<<< orphan*/  TXx9_SPMCR ; 
 int TXx9_SPMCR_BCLR ; 
 int TXx9_SPMCR_CONFIG ; 
 int TXx9_SPMCR_OPMODE ; 
 int TXx9_SPMCR_SPSTP ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned long long,int,int) ; 
 int /*<<< orphan*/ * devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct txx9spi*) ; 
 int devm_spi_register_master (int /*<<< orphan*/ *,struct spi_master*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 struct spi_master* spi_alloc_master (int /*<<< orphan*/ *,int) ; 
 struct txx9spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txx9spi_interrupt ; 
 int txx9spi_rd (struct txx9spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txx9spi_setup ; 
 int /*<<< orphan*/  txx9spi_transfer ; 
 int /*<<< orphan*/  txx9spi_work ; 
 int /*<<< orphan*/  txx9spi_wr (struct txx9spi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int txx9spi_probe(struct platform_device *dev)
{
	struct spi_master *master;
	struct txx9spi *c;
	struct resource *res;
	int ret = -ENODEV;
	u32 mcr;
	int irq;

	master = spi_alloc_master(&dev->dev, sizeof(*c));
	if (!master)
		return ret;
	c = spi_master_get_devdata(master);
	platform_set_drvdata(dev, master);

	INIT_WORK(&c->work, txx9spi_work);
	spin_lock_init(&c->lock);
	INIT_LIST_HEAD(&c->queue);
	init_waitqueue_head(&c->waitq);

	c->clk = devm_clk_get(&dev->dev, "spi-baseclk");
	if (IS_ERR(c->clk)) {
		ret = PTR_ERR(c->clk);
		c->clk = NULL;
		goto exit;
	}
	ret = clk_prepare_enable(c->clk);
	if (ret) {
		c->clk = NULL;
		goto exit;
	}
	c->baseclk = clk_get_rate(c->clk);
	master->min_speed_hz = DIV_ROUND_UP(c->baseclk, SPI_MAX_DIVIDER + 1);
	master->max_speed_hz = c->baseclk / (SPI_MIN_DIVIDER + 1);

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	c->membase = devm_ioremap_resource(&dev->dev, res);
	if (IS_ERR(c->membase))
		goto exit_busy;

	/* enter config mode */
	mcr = txx9spi_rd(c, TXx9_SPMCR);
	mcr &= ~(TXx9_SPMCR_OPMODE | TXx9_SPMCR_SPSTP | TXx9_SPMCR_BCLR);
	txx9spi_wr(c, mcr | TXx9_SPMCR_CONFIG | TXx9_SPMCR_BCLR, TXx9_SPMCR);

	irq = platform_get_irq(dev, 0);
	if (irq < 0)
		goto exit_busy;
	ret = devm_request_irq(&dev->dev, irq, txx9spi_interrupt, 0,
			       "spi_txx9", c);
	if (ret)
		goto exit;

	c->last_chipselect = -1;

	dev_info(&dev->dev, "at %#llx, irq %d, %dMHz\n",
		 (unsigned long long)res->start, irq,
		 (c->baseclk + 500000) / 1000000);

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CS_HIGH | SPI_CPOL | SPI_CPHA;

	master->bus_num = dev->id;
	master->setup = txx9spi_setup;
	master->transfer = txx9spi_transfer;
	master->num_chipselect = (u16)UINT_MAX; /* any GPIO numbers */
	master->bits_per_word_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16);

	ret = devm_spi_register_master(&dev->dev, master);
	if (ret)
		goto exit;
	return 0;
exit_busy:
	ret = -EBUSY;
exit:
	clk_disable_unprepare(c->clk);
	spi_master_put(master);
	return ret;
}