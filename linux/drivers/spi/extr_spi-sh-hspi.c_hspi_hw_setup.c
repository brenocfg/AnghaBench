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
struct spi_transfer {int /*<<< orphan*/  speed_hz; } ;
struct spi_message {struct spi_device* spi; } ;
struct spi_device {int mode; } ;
struct hspi_priv {int /*<<< orphan*/  clk; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPCR ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int /*<<< orphan*/  SPSCR ; 
 int /*<<< orphan*/  SPSR ; 
 int abs (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hspi_write (struct hspi_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hspi_hw_setup(struct hspi_priv *hspi,
			  struct spi_message *msg,
			  struct spi_transfer *t)
{
	struct spi_device *spi = msg->spi;
	struct device *dev = hspi->dev;
	u32 spcr, idiv_clk;
	u32 rate, best_rate, min, tmp;

	/*
	 * find best IDIV/CLKCx settings
	 */
	min = ~0;
	best_rate = 0;
	spcr = 0;
	for (idiv_clk = 0x00; idiv_clk <= 0x3F; idiv_clk++) {
		rate = clk_get_rate(hspi->clk);

		/* IDIV calculation */
		if (idiv_clk & (1 << 5))
			rate /= 128;
		else
			rate /= 16;

		/* CLKCx calculation */
		rate /= (((idiv_clk & 0x1F) + 1) * 2);

		/* save best settings */
		tmp = abs(t->speed_hz - rate);
		if (tmp < min) {
			min = tmp;
			spcr = idiv_clk;
			best_rate = rate;
		}
	}

	if (spi->mode & SPI_CPHA)
		spcr |= 1 << 7;
	if (spi->mode & SPI_CPOL)
		spcr |= 1 << 6;

	dev_dbg(dev, "speed %d/%d\n", t->speed_hz, best_rate);

	hspi_write(hspi, SPCR, spcr);
	hspi_write(hspi, SPSR, 0x0);
	hspi_write(hspi, SPSCR, 0x21);	/* master mode / CS control */
}