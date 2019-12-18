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
struct TYPE_2__ {int /*<<< orphan*/  txrx_bufs; int /*<<< orphan*/  setup_transfer; int /*<<< orphan*/  chipselect; struct spi_master* master; } ;
struct uwire_spi {TYPE_1__ bitbang; int /*<<< orphan*/  ck; } ;
struct spi_master {int mode_bits; int bus_num; int num_chipselect; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  setup; int /*<<< orphan*/  flags; int /*<<< orphan*/  bits_per_word_mask; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_BPW_RANGE_MASK (int,int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  SPI_MASTER_HALF_DUPLEX ; 
 int /*<<< orphan*/  UWIRE_BASE_PHYS ; 
 int /*<<< orphan*/  UWIRE_IO_SIZE ; 
 int /*<<< orphan*/  UWIRE_SR3 ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_omap7xx () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uwire_spi*) ; 
 struct spi_master* spi_alloc_master (int /*<<< orphan*/ *,int) ; 
 int spi_bitbang_start (TYPE_1__*) ; 
 struct uwire_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  uwire_base ; 
 int /*<<< orphan*/  uwire_chipselect ; 
 int /*<<< orphan*/  uwire_cleanup ; 
 int uwire_idx_shift ; 
 int /*<<< orphan*/  uwire_off (struct uwire_spi*) ; 
 int /*<<< orphan*/  uwire_setup ; 
 int /*<<< orphan*/  uwire_setup_transfer ; 
 int /*<<< orphan*/  uwire_txrx ; 
 int /*<<< orphan*/  uwire_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uwire_probe(struct platform_device *pdev)
{
	struct spi_master	*master;
	struct uwire_spi	*uwire;
	int			status;

	master = spi_alloc_master(&pdev->dev, sizeof *uwire);
	if (!master)
		return -ENODEV;

	uwire = spi_master_get_devdata(master);

	uwire_base = devm_ioremap(&pdev->dev, UWIRE_BASE_PHYS, UWIRE_IO_SIZE);
	if (!uwire_base) {
		dev_dbg(&pdev->dev, "can't ioremap UWIRE\n");
		spi_master_put(master);
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, uwire);

	uwire->ck = devm_clk_get(&pdev->dev, "fck");
	if (IS_ERR(uwire->ck)) {
		status = PTR_ERR(uwire->ck);
		dev_dbg(&pdev->dev, "no functional clock?\n");
		spi_master_put(master);
		return status;
	}
	clk_enable(uwire->ck);

	if (cpu_is_omap7xx())
		uwire_idx_shift = 1;
	else
		uwire_idx_shift = 2;

	uwire_write_reg(UWIRE_SR3, 1);

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 16);
	master->flags = SPI_MASTER_HALF_DUPLEX;

	master->bus_num = 2;	/* "official" */
	master->num_chipselect = 4;
	master->setup = uwire_setup;
	master->cleanup = uwire_cleanup;

	uwire->bitbang.master = master;
	uwire->bitbang.chipselect = uwire_chipselect;
	uwire->bitbang.setup_transfer = uwire_setup_transfer;
	uwire->bitbang.txrx_bufs = uwire_txrx;

	status = spi_bitbang_start(&uwire->bitbang);
	if (status < 0) {
		uwire_off(uwire);
	}
	return status;
}