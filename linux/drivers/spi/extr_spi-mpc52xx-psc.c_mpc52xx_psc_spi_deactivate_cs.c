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
struct spi_device {int mode; int /*<<< orphan*/  master; } ;
struct mpc52xx_psc_spi {int /*<<< orphan*/  (* cs_control ) (struct spi_device*,int) ;} ;

/* Variables and functions */
 int SPI_CS_HIGH ; 
 struct mpc52xx_psc_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct spi_device*,int) ; 

__attribute__((used)) static void mpc52xx_psc_spi_deactivate_cs(struct spi_device *spi)
{
	struct mpc52xx_psc_spi *mps = spi_master_get_devdata(spi->master);

	if (mps->cs_control)
		mps->cs_control(spi, (spi->mode & SPI_CS_HIGH) ? 0 : 1);
}