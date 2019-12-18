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
struct fbtft_par {TYPE_1__* info; TYPE_2__* spi; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gain ; 
 int load ; 
 int pot ; 
 int pump ; 
 int ratio ; 
 int spi_setup (TYPE_2__*) ; 
 int temp ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	int ret;

	/* Set CS active high */
	par->spi->mode |= SPI_CS_HIGH;
	ret = spi_setup(par->spi);
	if (ret) {
		dev_err(par->info->device, "Could not set SPI_CS_HIGH\n");
		return ret;
	}

	/* Reset controller */
	write_reg(par, 0xE2);

	/* Set bias ratio */
	write_reg(par, 0xE8 | (ratio & 0x03));

	/* Set bias gain and potentiometer */
	write_reg(par, 0x81);
	write_reg(par, (gain & 0x03) << 6 | (pot & 0x3F));

	/* Set temperature compensation */
	write_reg(par, 0x24 | (temp & 0x03));

	/* Set panel loading */
	write_reg(par, 0x28 | (load & 0x03));

	/* Set pump control */
	write_reg(par, 0x2C | (pump & 0x03));

	/* Set inverse display */
	write_reg(par, 0xA6 | (0x01 & 0x01));

	/* Set 4-bit grayscale mode */
	write_reg(par, 0xD0 | (0x02 & 0x03));

	/* Set Display enable */
	write_reg(par, 0xA8 | 0x07);

	return 0;
}