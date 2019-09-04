#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mtd_info {scalar_t__ size; } ;
struct TYPE_3__ {int /*<<< orphan*/  unprepare; int /*<<< orphan*/  prepare; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; int /*<<< orphan*/  erase; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct mtd_info mtd; struct stm32_qspi_flash* priv; int /*<<< orphan*/  dev; } ;
struct stm32_qspi_flash {int cs; int presc; scalar_t__ prefetch_limit; scalar_t__ read_mode; int registered; void* fsize; TYPE_1__ nor; struct stm32_qspi* qspi; } ;
struct stm32_qspi {scalar_t__ mm_size; int /*<<< orphan*/  dev; scalar_t__ io_base; struct stm32_qspi_flash* flash; int /*<<< orphan*/  clk_rate; } ;
struct spi_nor_hwcaps {int mask; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCR_FMODE_INDR ; 
 scalar_t__ CCR_FMODE_MM ; 
 int CR_EN ; 
 int CR_FTHRES (int) ; 
 int CR_PRESC (int) ; 
 int CR_SSHIFT ; 
 int CR_TCEN ; 
 int DCR_CSHT (int) ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 void* FSIZE_VAL (scalar_t__) ; 
 int LPTR_DFT_TIMEOUT ; 
 scalar_t__ QUADSPI_CR ; 
 scalar_t__ QUADSPI_DCR ; 
 scalar_t__ QUADSPI_LPTR ; 
 int SNOR_HWCAPS_PP ; 
 int SNOR_HWCAPS_READ ; 
 int SNOR_HWCAPS_READ_1_1_2 ; 
 int SNOR_HWCAPS_READ_1_1_4 ; 
 int SNOR_HWCAPS_READ_FAST ; 
 int STM32_MAX_NORCHIP ; 
 scalar_t__ STM32_QSPI_FIFO_SZ ; 
 scalar_t__ SZ_1K ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 int spi_nor_scan (TYPE_1__*,int /*<<< orphan*/ *,struct spi_nor_hwcaps*) ; 
 int /*<<< orphan*/  spi_nor_set_flash_node (TYPE_1__*,struct device_node*) ; 
 int /*<<< orphan*/  stm32_qspi_erase ; 
 int /*<<< orphan*/  stm32_qspi_prep ; 
 int /*<<< orphan*/  stm32_qspi_read ; 
 int /*<<< orphan*/  stm32_qspi_read_reg ; 
 int /*<<< orphan*/  stm32_qspi_unprep ; 
 int /*<<< orphan*/  stm32_qspi_write ; 
 int /*<<< orphan*/  stm32_qspi_write_reg ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32_qspi_flash_setup(struct stm32_qspi *qspi,
				  struct device_node *np)
{
	struct spi_nor_hwcaps hwcaps = {
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_PP,
	};
	u32 width, presc, cs_num, max_rate = 0;
	struct stm32_qspi_flash *flash;
	struct mtd_info *mtd;
	int ret;

	of_property_read_u32(np, "reg", &cs_num);
	if (cs_num >= STM32_MAX_NORCHIP)
		return -EINVAL;

	of_property_read_u32(np, "spi-max-frequency", &max_rate);
	if (!max_rate)
		return -EINVAL;

	presc = DIV_ROUND_UP(qspi->clk_rate, max_rate) - 1;

	if (of_property_read_u32(np, "spi-rx-bus-width", &width))
		width = 1;

	if (width == 4)
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_4;
	else if (width == 2)
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_2;
	else if (width != 1)
		return -EINVAL;

	flash = &qspi->flash[cs_num];
	flash->qspi = qspi;
	flash->cs = cs_num;
	flash->presc = presc;

	flash->nor.dev = qspi->dev;
	spi_nor_set_flash_node(&flash->nor, np);
	flash->nor.priv = flash;
	mtd = &flash->nor.mtd;

	flash->nor.read = stm32_qspi_read;
	flash->nor.write = stm32_qspi_write;
	flash->nor.erase = stm32_qspi_erase;
	flash->nor.read_reg = stm32_qspi_read_reg;
	flash->nor.write_reg = stm32_qspi_write_reg;
	flash->nor.prepare = stm32_qspi_prep;
	flash->nor.unprepare = stm32_qspi_unprep;

	writel_relaxed(LPTR_DFT_TIMEOUT, qspi->io_base + QUADSPI_LPTR);

	writel_relaxed(CR_PRESC(presc) | CR_FTHRES(3) | CR_TCEN | CR_SSHIFT
		       | CR_EN, qspi->io_base + QUADSPI_CR);

	/*
	 * in stm32 qspi controller, QUADSPI_DCR register has a fsize field
	 * which define the size of nor flash.
	 * if fsize is NULL, the controller can't sent spi-nor command.
	 * set a temporary value just to discover the nor flash with
	 * "spi_nor_scan". After, the right value (mtd->size) can be set.
	 */
	flash->fsize = FSIZE_VAL(SZ_1K);

	ret = spi_nor_scan(&flash->nor, NULL, &hwcaps);
	if (ret) {
		dev_err(qspi->dev, "device scan failed\n");
		return ret;
	}

	flash->fsize = FSIZE_VAL(mtd->size);
	flash->prefetch_limit = mtd->size - STM32_QSPI_FIFO_SZ;

	flash->read_mode = CCR_FMODE_MM;
	if (mtd->size > qspi->mm_size)
		flash->read_mode = CCR_FMODE_INDR;

	writel_relaxed(DCR_CSHT(1), qspi->io_base + QUADSPI_DCR);

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret) {
		dev_err(qspi->dev, "mtd device parse failed\n");
		return ret;
	}

	flash->registered = true;

	dev_dbg(qspi->dev, "read mm:%s cs:%d bus:%d\n",
		flash->read_mode == CCR_FMODE_MM ? "yes" : "no", cs_num, width);

	return 0;
}