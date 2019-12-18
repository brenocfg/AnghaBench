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
struct synquacer_spi {unsigned int speed; unsigned int bus_width; unsigned int bpw; unsigned int mode; unsigned int cs; unsigned int transfer_mode; scalar_t__ regs; scalar_t__ rtm; scalar_t__ aces; int /*<<< orphan*/  dev; } ;
struct spi_transfer {int rx_nbits; int tx_nbits; unsigned int speed_hz; unsigned int bits_per_word; scalar_t__ rx_buf; scalar_t__ tx_buf; } ;
struct spi_master {int max_speed_hz; } ;
struct spi_device {unsigned int mode; unsigned int chip_select; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,unsigned int) ; 
 int EINVAL ; 
 unsigned int SPI_CPHA ; 
 unsigned int SPI_CPOL ; 
 unsigned int SPI_CS_HIGH ; 
 unsigned int SPI_LSB_FIRST ; 
 unsigned int SPI_RX_DUAL ; 
 unsigned int SPI_RX_QUAD ; 
 unsigned int SPI_TX_DUAL ; 
 unsigned int SPI_TX_QUAD ; 
 int SYNQUACER_HSSPI_DMTRP_BUS_WIDTH_SHIFT ; 
 int SYNQUACER_HSSPI_DMTRP_DATA_MASK ; 
 int SYNQUACER_HSSPI_DMTRP_DATA_RX ; 
 int SYNQUACER_HSSPI_DMTRP_DATA_SHIFT ; 
 int SYNQUACER_HSSPI_DMTRP_DATA_TX ; 
 int SYNQUACER_HSSPI_FIFOCFG_FIFO_WIDTH_MASK ; 
 int SYNQUACER_HSSPI_FIFOCFG_FIFO_WIDTH_SHIFT ; 
 int SYNQUACER_HSSPI_PCC_ACES ; 
 int SYNQUACER_HSSPI_PCC_CDRS_MASK ; 
 int SYNQUACER_HSSPI_PCC_CDRS_SHIFT ; 
 int SYNQUACER_HSSPI_PCC_CPHA ; 
 int SYNQUACER_HSSPI_PCC_CPOL ; 
 int SYNQUACER_HSSPI_PCC_RTM ; 
 int SYNQUACER_HSSPI_PCC_SAFESYNC ; 
 int SYNQUACER_HSSPI_PCC_SDIR ; 
 int SYNQUACER_HSSPI_PCC_SENDIAN ; 
 int SYNQUACER_HSSPI_PCC_SS2CD_SHIFT ; 
 int SYNQUACER_HSSPI_PCC_SSPOL ; 
 scalar_t__ SYNQUACER_HSSPI_REG_DMSTART ; 
 scalar_t__ SYNQUACER_HSSPI_REG_FIFOCFG ; 
 scalar_t__ SYNQUACER_HSSPI_REG_PCC (unsigned int) ; 
 unsigned int SYNQUACER_HSSPI_TRANSFER_MODE_RX ; 
 unsigned int SYNQUACER_HSSPI_TRANSFER_MODE_TX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int readl (scalar_t__) ; 
 struct synquacer_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int synquacer_spi_config(struct spi_master *master,
				struct spi_device *spi,
				struct spi_transfer *xfer)
{
	struct synquacer_spi *sspi = spi_master_get_devdata(master);
	unsigned int speed, mode, bpw, cs, bus_width, transfer_mode;
	u32 rate, val, div;

	/* Full Duplex only on 1-bit wide bus */
	if (xfer->rx_buf && xfer->tx_buf &&
	    (xfer->rx_nbits != 1 || xfer->tx_nbits != 1)) {
		dev_err(sspi->dev,
			"RX and TX bus widths must be 1-bit for Full-Duplex!\n");
		return -EINVAL;
	}

	if (xfer->tx_buf) {
		bus_width = xfer->tx_nbits;
		transfer_mode = SYNQUACER_HSSPI_TRANSFER_MODE_TX;
	} else {
		bus_width = xfer->rx_nbits;
		transfer_mode = SYNQUACER_HSSPI_TRANSFER_MODE_RX;
	}

	mode = spi->mode;
	cs = spi->chip_select;
	speed = xfer->speed_hz;
	bpw = xfer->bits_per_word;

	/* return if nothing to change */
	if (speed == sspi->speed &&
		bus_width == sspi->bus_width && bpw == sspi->bpw &&
		mode == sspi->mode && cs == sspi->cs &&
		transfer_mode == sspi->transfer_mode) {
		return 0;
	}

	sspi->transfer_mode = transfer_mode;
	rate = master->max_speed_hz;

	div = DIV_ROUND_UP(rate, speed);
	if (div > 254) {
		dev_err(sspi->dev, "Requested rate too low (%u)\n",
			sspi->speed);
		return -EINVAL;
	}

	val = readl(sspi->regs + SYNQUACER_HSSPI_REG_PCC(cs));
	val &= ~SYNQUACER_HSSPI_PCC_SAFESYNC;
	if (bpw == 8 &&	(mode & (SPI_TX_DUAL | SPI_RX_DUAL)) && div < 3)
		val |= SYNQUACER_HSSPI_PCC_SAFESYNC;
	if (bpw == 8 &&	(mode & (SPI_TX_QUAD | SPI_RX_QUAD)) && div < 6)
		val |= SYNQUACER_HSSPI_PCC_SAFESYNC;
	if (bpw == 16 && (mode & (SPI_TX_QUAD | SPI_RX_QUAD)) && div < 3)
		val |= SYNQUACER_HSSPI_PCC_SAFESYNC;

	if (mode & SPI_CPHA)
		val |= SYNQUACER_HSSPI_PCC_CPHA;
	else
		val &= ~SYNQUACER_HSSPI_PCC_CPHA;

	if (mode & SPI_CPOL)
		val |= SYNQUACER_HSSPI_PCC_CPOL;
	else
		val &= ~SYNQUACER_HSSPI_PCC_CPOL;

	if (mode & SPI_CS_HIGH)
		val |= SYNQUACER_HSSPI_PCC_SSPOL;
	else
		val &= ~SYNQUACER_HSSPI_PCC_SSPOL;

	if (mode & SPI_LSB_FIRST)
		val |= SYNQUACER_HSSPI_PCC_SDIR;
	else
		val &= ~SYNQUACER_HSSPI_PCC_SDIR;

	if (sspi->aces)
		val |= SYNQUACER_HSSPI_PCC_ACES;
	else
		val &= ~SYNQUACER_HSSPI_PCC_ACES;

	if (sspi->rtm)
		val |= SYNQUACER_HSSPI_PCC_RTM;
	else
		val &= ~SYNQUACER_HSSPI_PCC_RTM;

	val |= (3 << SYNQUACER_HSSPI_PCC_SS2CD_SHIFT);
	val |= SYNQUACER_HSSPI_PCC_SENDIAN;

	val &= ~(SYNQUACER_HSSPI_PCC_CDRS_MASK <<
		 SYNQUACER_HSSPI_PCC_CDRS_SHIFT);
	val |= ((div >> 1) << SYNQUACER_HSSPI_PCC_CDRS_SHIFT);

	writel(val, sspi->regs + SYNQUACER_HSSPI_REG_PCC(cs));

	val = readl(sspi->regs + SYNQUACER_HSSPI_REG_FIFOCFG);
	val &= ~(SYNQUACER_HSSPI_FIFOCFG_FIFO_WIDTH_MASK <<
		 SYNQUACER_HSSPI_FIFOCFG_FIFO_WIDTH_SHIFT);
	val |= ((bpw / 8 - 1) << SYNQUACER_HSSPI_FIFOCFG_FIFO_WIDTH_SHIFT);
	writel(val, sspi->regs + SYNQUACER_HSSPI_REG_FIFOCFG);

	val = readl(sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);
	val &= ~(SYNQUACER_HSSPI_DMTRP_DATA_MASK <<
		 SYNQUACER_HSSPI_DMTRP_DATA_SHIFT);

	if (xfer->rx_buf)
		val |= (SYNQUACER_HSSPI_DMTRP_DATA_RX <<
			SYNQUACER_HSSPI_DMTRP_DATA_SHIFT);
	else
		val |= (SYNQUACER_HSSPI_DMTRP_DATA_TX <<
			SYNQUACER_HSSPI_DMTRP_DATA_SHIFT);

	val &= ~(3 << SYNQUACER_HSSPI_DMTRP_BUS_WIDTH_SHIFT);
	val |= ((bus_width >> 1) << SYNQUACER_HSSPI_DMTRP_BUS_WIDTH_SHIFT);
	writel(val, sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);

	sspi->bpw = bpw;
	sspi->mode = mode;
	sspi->speed = speed;
	sspi->cs = spi->chip_select;
	sspi->bus_width = bus_width;

	return 0;
}