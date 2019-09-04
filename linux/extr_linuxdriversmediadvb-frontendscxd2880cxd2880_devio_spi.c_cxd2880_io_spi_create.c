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
typedef  int /*<<< orphan*/  u8 ;
struct cxd2880_spi {int dummy; } ;
struct cxd2880_io {int /*<<< orphan*/  slave_select; scalar_t__ i2c_address_demod; scalar_t__ i2c_address_sys; struct cxd2880_spi* if_object; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  write_regs; int /*<<< orphan*/  read_regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cxd2880_io_common_write_one_reg ; 
 int /*<<< orphan*/  cxd2880_io_spi_read_reg ; 
 int /*<<< orphan*/  cxd2880_io_spi_write_reg ; 

int cxd2880_io_spi_create(struct cxd2880_io *io,
			  struct cxd2880_spi *spi, u8 slave_select)
{
	if (!io || !spi)
		return -EINVAL;

	io->read_regs = cxd2880_io_spi_read_reg;
	io->write_regs = cxd2880_io_spi_write_reg;
	io->write_reg = cxd2880_io_common_write_one_reg;
	io->if_object = spi;
	io->i2c_address_sys = 0;
	io->i2c_address_demod = 0;
	io->slave_select = slave_select;

	return 0;
}