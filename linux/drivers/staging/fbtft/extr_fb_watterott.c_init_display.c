#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  write_vmem; int /*<<< orphan*/  (* reset ) (struct fbtft_par*) ;} ;
struct fbtft_par {TYPE_2__ fbtftops; TYPE_1__* info; TYPE_3__* spi; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INIT_DISPLAY ; 
 int /*<<< orphan*/  SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fbtft_par_dbg (int /*<<< orphan*/ ,struct fbtft_par*,char*,unsigned int,unsigned int) ; 
 unsigned int firmware_version (struct fbtft_par*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mode ; 
 int spi_setup (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 
 int /*<<< orphan*/  write_vmem_8bit ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	int ret;
	unsigned int version;
	u8 save_mode;

	/* enable SPI interface by having CS and MOSI low during reset */
	save_mode = par->spi->mode;
	par->spi->mode |= SPI_CS_HIGH;
	ret = spi_setup(par->spi); /* set CS inactive low */
	if (ret) {
		dev_err(par->info->device, "Could not set SPI_CS_HIGH\n");
		return ret;
	}
	write_reg(par, 0x00); /* make sure mode is set */

	mdelay(50);
	par->fbtftops.reset(par);
	mdelay(1000);
	par->spi->mode = save_mode;
	ret = spi_setup(par->spi);
	if (ret) {
		dev_err(par->info->device, "Could not restore SPI mode\n");
		return ret;
	}
	write_reg(par, 0x00);

	version = firmware_version(par);
	fbtft_par_dbg(DEBUG_INIT_DISPLAY, par, "Firmware version: %x.%02x\n",
		      version >> 8, version & 0xFF);

	if (mode == 332)
		par->fbtftops.write_vmem = write_vmem_8bit;
	return 0;
}