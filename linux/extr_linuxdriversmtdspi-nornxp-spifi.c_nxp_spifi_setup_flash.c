#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct spi_nor_hwcaps {int mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtd; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; int /*<<< orphan*/  erase; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct nxp_spifi* priv; int /*<<< orphan*/  dev; } ;
struct nxp_spifi {int /*<<< orphan*/  dev; TYPE_1__ nor; scalar_t__ io_base; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNOR_HWCAPS_PP ; 
 int SNOR_HWCAPS_READ ; 
 int SNOR_HWCAPS_READ_1_1_2 ; 
 int SNOR_HWCAPS_READ_1_1_4 ; 
 int SNOR_HWCAPS_READ_FAST ; 
 scalar_t__ SPIFI_CTRL ; 
 int SPIFI_CTRL_CSHIGH (int) ; 
 int SPIFI_CTRL_DUAL ; 
 int SPIFI_CTRL_FBCLK ; 
 int SPIFI_CTRL_MODE3 ; 
 int SPIFI_CTRL_TIMEOUT (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
#define  SPI_MODE_0 129 
#define  SPI_MODE_3 128 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mtd_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nxp_spifi_dummy_id_read (TYPE_1__*) ; 
 int /*<<< orphan*/  nxp_spifi_erase ; 
 int /*<<< orphan*/  nxp_spifi_read ; 
 int /*<<< orphan*/  nxp_spifi_read_reg ; 
 int nxp_spifi_setup_memory_cmd (struct nxp_spifi*) ; 
 int /*<<< orphan*/  nxp_spifi_write ; 
 int /*<<< orphan*/  nxp_spifi_write_reg ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int spi_nor_scan (TYPE_1__*,int /*<<< orphan*/ *,struct spi_nor_hwcaps*) ; 
 int /*<<< orphan*/  spi_nor_set_flash_node (TYPE_1__*,struct device_node*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int nxp_spifi_setup_flash(struct nxp_spifi *spifi,
				 struct device_node *np)
{
	struct spi_nor_hwcaps hwcaps = {
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_PP,
	};
	u32 ctrl, property;
	u16 mode = 0;
	int ret;

	if (!of_property_read_u32(np, "spi-rx-bus-width", &property)) {
		switch (property) {
		case 1:
			break;
		case 2:
			mode |= SPI_RX_DUAL;
			break;
		case 4:
			mode |= SPI_RX_QUAD;
			break;
		default:
			dev_err(spifi->dev, "unsupported rx-bus-width\n");
			return -EINVAL;
		}
	}

	if (of_find_property(np, "spi-cpha", NULL))
		mode |= SPI_CPHA;

	if (of_find_property(np, "spi-cpol", NULL))
		mode |= SPI_CPOL;

	/* Setup control register defaults */
	ctrl = SPIFI_CTRL_TIMEOUT(1000) |
	       SPIFI_CTRL_CSHIGH(15) |
	       SPIFI_CTRL_FBCLK;

	if (mode & SPI_RX_DUAL) {
		ctrl |= SPIFI_CTRL_DUAL;
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_2;
	} else if (mode & SPI_RX_QUAD) {
		ctrl &= ~SPIFI_CTRL_DUAL;
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_4;
	} else {
		ctrl |= SPIFI_CTRL_DUAL;
	}

	switch (mode & (SPI_CPHA | SPI_CPOL)) {
	case SPI_MODE_0:
		ctrl &= ~SPIFI_CTRL_MODE3;
		break;
	case SPI_MODE_3:
		ctrl |= SPIFI_CTRL_MODE3;
		break;
	default:
		dev_err(spifi->dev, "only mode 0 and 3 supported\n");
		return -EINVAL;
	}

	writel(ctrl, spifi->io_base + SPIFI_CTRL);

	spifi->nor.dev   = spifi->dev;
	spi_nor_set_flash_node(&spifi->nor, np);
	spifi->nor.priv  = spifi;
	spifi->nor.read  = nxp_spifi_read;
	spifi->nor.write = nxp_spifi_write;
	spifi->nor.erase = nxp_spifi_erase;
	spifi->nor.read_reg  = nxp_spifi_read_reg;
	spifi->nor.write_reg = nxp_spifi_write_reg;

	/*
	 * The first read on a hard reset isn't reliable so do a
	 * dummy read of the id before calling spi_nor_scan().
	 * The reason for this problem is unknown.
	 *
	 * The official NXP spifilib uses more or less the same
	 * workaround that is applied here by reading the device
	 * id multiple times.
	 */
	nxp_spifi_dummy_id_read(&spifi->nor);

	ret = spi_nor_scan(&spifi->nor, NULL, &hwcaps);
	if (ret) {
		dev_err(spifi->dev, "device scan failed\n");
		return ret;
	}

	ret = nxp_spifi_setup_memory_cmd(spifi);
	if (ret) {
		dev_err(spifi->dev, "memory command setup failed\n");
		return ret;
	}

	ret = mtd_device_register(&spifi->nor.mtd, NULL, 0);
	if (ret) {
		dev_err(spifi->dev, "mtd device parse failed\n");
		return ret;
	}

	return 0;
}