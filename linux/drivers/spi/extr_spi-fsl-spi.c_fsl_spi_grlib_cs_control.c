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
typedef  int u16 ;
struct spi_device {int chip_select; scalar_t__ cs_gpiod; int /*<<< orphan*/  master; } ;
struct mpc8xxx_spi {int native_chipselects; struct fsl_spi_reg* reg_base; } ;
struct fsl_spi_reg {int /*<<< orphan*/  slvsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int mpc8xxx_spi_read_reg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc8xxx_spi_write_reg (int /*<<< orphan*/ *,int) ; 
 struct mpc8xxx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_spi_grlib_cs_control(struct spi_device *spi, bool on)
{
	struct mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(spi->master);
	struct fsl_spi_reg *reg_base = mpc8xxx_spi->reg_base;
	u32 slvsel;
	u16 cs = spi->chip_select;

	if (spi->cs_gpiod) {
		gpiod_set_value(spi->cs_gpiod, on);
	} else if (cs < mpc8xxx_spi->native_chipselects) {
		slvsel = mpc8xxx_spi_read_reg(&reg_base->slvsel);
		slvsel = on ? (slvsel | (1 << cs)) : (slvsel & ~(1 << cs));
		mpc8xxx_spi_write_reg(&reg_base->slvsel, slvsel);
	}
}