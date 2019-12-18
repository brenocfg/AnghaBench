#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {int mode; int /*<<< orphan*/  max_speed_hz; TYPE_2__ dev; int /*<<< orphan*/  controller; } ;
struct fsl_dspi_platform_data {int /*<<< orphan*/  sck_cs_delay; int /*<<< orphan*/  cs_sck_delay; } ;
struct fsl_dspi {int /*<<< orphan*/  ctlr; int /*<<< orphan*/  clk; TYPE_1__* pdev; } ;
struct chip_data {int ctar_val; scalar_t__ void_write_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CTAR_ASC (unsigned char) ; 
 int SPI_CTAR_BR (unsigned char) ; 
 int SPI_CTAR_CPHA ; 
 int SPI_CTAR_CPOL ; 
 int SPI_CTAR_CSSCK (unsigned char) ; 
 int SPI_CTAR_LSBFE ; 
 int SPI_CTAR_PASC (unsigned char) ; 
 int SPI_CTAR_PBR (unsigned char) ; 
 int SPI_CTAR_PCSSCK (unsigned char) ; 
 int SPI_LSB_FIRST ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 struct fsl_dspi_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz_to_spi_baud (unsigned char*,unsigned char*,int /*<<< orphan*/ ,unsigned long) ; 
 struct chip_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_delay_scale (unsigned char*,unsigned char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct fsl_dspi* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_controller_is_slave (int /*<<< orphan*/ ) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,struct chip_data*) ; 

__attribute__((used)) static int dspi_setup(struct spi_device *spi)
{
	struct fsl_dspi *dspi = spi_controller_get_devdata(spi->controller);
	unsigned char br = 0, pbr = 0, pcssck = 0, cssck = 0;
	u32 cs_sck_delay = 0, sck_cs_delay = 0;
	struct fsl_dspi_platform_data *pdata;
	unsigned char pasc = 0, asc = 0;
	struct chip_data *chip;
	unsigned long clkrate;

	/* Only alloc on first setup */
	chip = spi_get_ctldata(spi);
	if (chip == NULL) {
		chip = kzalloc(sizeof(struct chip_data), GFP_KERNEL);
		if (!chip)
			return -ENOMEM;
	}

	pdata = dev_get_platdata(&dspi->pdev->dev);

	if (!pdata) {
		of_property_read_u32(spi->dev.of_node, "fsl,spi-cs-sck-delay",
				     &cs_sck_delay);

		of_property_read_u32(spi->dev.of_node, "fsl,spi-sck-cs-delay",
				     &sck_cs_delay);
	} else {
		cs_sck_delay = pdata->cs_sck_delay;
		sck_cs_delay = pdata->sck_cs_delay;
	}

	chip->void_write_data = 0;

	clkrate = clk_get_rate(dspi->clk);
	hz_to_spi_baud(&pbr, &br, spi->max_speed_hz, clkrate);

	/* Set PCS to SCK delay scale values */
	ns_delay_scale(&pcssck, &cssck, cs_sck_delay, clkrate);

	/* Set After SCK delay scale values */
	ns_delay_scale(&pasc, &asc, sck_cs_delay, clkrate);

	chip->ctar_val = 0;
	if (spi->mode & SPI_CPOL)
		chip->ctar_val |= SPI_CTAR_CPOL;
	if (spi->mode & SPI_CPHA)
		chip->ctar_val |= SPI_CTAR_CPHA;

	if (!spi_controller_is_slave(dspi->ctlr)) {
		chip->ctar_val |= SPI_CTAR_PCSSCK(pcssck) |
				  SPI_CTAR_CSSCK(cssck) |
				  SPI_CTAR_PASC(pasc) |
				  SPI_CTAR_ASC(asc) |
				  SPI_CTAR_PBR(pbr) |
				  SPI_CTAR_BR(br);

		if (spi->mode & SPI_LSB_FIRST)
			chip->ctar_val |= SPI_CTAR_LSBFE;
	}

	spi_set_ctldata(spi, chip);

	return 0;
}