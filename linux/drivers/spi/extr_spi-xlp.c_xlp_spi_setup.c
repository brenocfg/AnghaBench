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
struct xlp_spi_priv {int /*<<< orphan*/  spi_clk; } ;
struct spi_device {int chip_select; int mode; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  XLP_SPI_CONFIG ; 
 int XLP_SPI_CPHA ; 
 int XLP_SPI_CPOL ; 
 int XLP_SPI_CS_LSBFE ; 
 int XLP_SPI_CS_POL ; 
 int /*<<< orphan*/  XLP_SPI_FDIV ; 
 int XLP_SPI_FDIV_MAX ; 
 int XLP_SPI_FDIV_MIN ; 
 int /*<<< orphan*/  XLP_SPI_FIFO_THRESH ; 
 int XLP_SPI_RXCAP_EN ; 
 int XLP_SPI_RXMISO_EN ; 
 int XLP_SPI_TXMOSI_EN ; 
 int XLP_SPI_TXRXTH ; 
 struct xlp_spi_priv* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int xlp_spi_reg_read (struct xlp_spi_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp_spi_reg_write (struct xlp_spi_priv*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xlp_spi_setup(struct spi_device *spi)
{
	struct xlp_spi_priv *xspi;
	u32 fdiv, cfg;
	int cs;

	xspi = spi_master_get_devdata(spi->master);
	cs = spi->chip_select;
	/*
	 * The value of fdiv must be between 4 and 65535.
	 */
	fdiv = DIV_ROUND_UP(xspi->spi_clk, spi->max_speed_hz);
	if (fdiv > XLP_SPI_FDIV_MAX)
		fdiv = XLP_SPI_FDIV_MAX;
	else if (fdiv < XLP_SPI_FDIV_MIN)
		fdiv = XLP_SPI_FDIV_MIN;

	xlp_spi_reg_write(xspi, cs, XLP_SPI_FDIV, fdiv);
	xlp_spi_reg_write(xspi, cs, XLP_SPI_FIFO_THRESH, XLP_SPI_TXRXTH);
	cfg = xlp_spi_reg_read(xspi, cs, XLP_SPI_CONFIG);
	if (spi->mode & SPI_CPHA)
		cfg |= XLP_SPI_CPHA;
	else
		cfg &= ~XLP_SPI_CPHA;
	if (spi->mode & SPI_CPOL)
		cfg |= XLP_SPI_CPOL;
	else
		cfg &= ~XLP_SPI_CPOL;
	if (!(spi->mode & SPI_CS_HIGH))
		cfg |= XLP_SPI_CS_POL;
	else
		cfg &= ~XLP_SPI_CS_POL;
	if (spi->mode & SPI_LSB_FIRST)
		cfg |= XLP_SPI_CS_LSBFE;
	else
		cfg &= ~XLP_SPI_CS_LSBFE;

	cfg |= XLP_SPI_TXMOSI_EN | XLP_SPI_RXMISO_EN;
	if (fdiv == 4)
		cfg |= XLP_SPI_RXCAP_EN;
	xlp_spi_reg_write(xspi, cs, XLP_SPI_CONFIG, cfg);

	return 0;
}