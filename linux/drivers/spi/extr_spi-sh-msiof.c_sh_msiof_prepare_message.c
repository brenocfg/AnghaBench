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
struct spi_message {struct spi_device* spi; } ;
struct spi_device {int chip_select; int mode; scalar_t__ cs_gpiod; } ;
struct spi_controller {int dummy; } ;
struct sh_msiof_spi_priv {int unused_ss; int native_cs_high; } ;

/* Variables and functions */
 int SPI_3WIRE ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  sh_msiof_spi_set_pin_regs (struct sh_msiof_spi_priv*,int,int,int,int,int,int) ; 
 struct sh_msiof_spi_priv* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int sh_msiof_prepare_message(struct spi_controller *ctlr,
				    struct spi_message *msg)
{
	struct sh_msiof_spi_priv *p = spi_controller_get_devdata(ctlr);
	const struct spi_device *spi = msg->spi;
	u32 ss, cs_high;

	/* Configure pins before asserting CS */
	if (spi->cs_gpiod) {
		ss = p->unused_ss;
		cs_high = p->native_cs_high;
	} else {
		ss = spi->chip_select;
		cs_high = !!(spi->mode & SPI_CS_HIGH);
	}
	sh_msiof_spi_set_pin_regs(p, ss, !!(spi->mode & SPI_CPOL),
				  !!(spi->mode & SPI_CPHA),
				  !!(spi->mode & SPI_3WIRE),
				  !!(spi->mode & SPI_LSB_FIRST), cs_high);
	return 0;
}