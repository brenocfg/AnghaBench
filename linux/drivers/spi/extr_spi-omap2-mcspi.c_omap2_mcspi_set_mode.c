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
typedef  int /*<<< orphan*/  u32 ;
struct spi_master {int dummy; } ;
struct omap2_mcspi_regs {int /*<<< orphan*/  modulctrl; } ;
struct omap2_mcspi {struct omap2_mcspi_regs ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_MCSPI_MODULCTRL ; 
 int /*<<< orphan*/  OMAP2_MCSPI_MODULCTRL_MS ; 
 int /*<<< orphan*/  OMAP2_MCSPI_MODULCTRL_SINGLE ; 
 int /*<<< orphan*/  OMAP2_MCSPI_MODULCTRL_STEST ; 
 int /*<<< orphan*/  mcspi_read_reg (struct spi_master*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcspi_write_reg (struct spi_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spi_controller_is_slave (struct spi_master*) ; 
 struct omap2_mcspi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static void omap2_mcspi_set_mode(struct spi_master *master)
{
	struct omap2_mcspi	*mcspi = spi_master_get_devdata(master);
	struct omap2_mcspi_regs	*ctx = &mcspi->ctx;
	u32 l;

	/*
	 * Choose master or slave mode
	 */
	l = mcspi_read_reg(master, OMAP2_MCSPI_MODULCTRL);
	l &= ~(OMAP2_MCSPI_MODULCTRL_STEST);
	if (spi_controller_is_slave(master)) {
		l |= (OMAP2_MCSPI_MODULCTRL_MS);
	} else {
		l &= ~(OMAP2_MCSPI_MODULCTRL_MS);
		l |= OMAP2_MCSPI_MODULCTRL_SINGLE;
	}
	mcspi_write_reg(master, OMAP2_MCSPI_MODULCTRL, l);

	ctx->modulctrl = l;
}