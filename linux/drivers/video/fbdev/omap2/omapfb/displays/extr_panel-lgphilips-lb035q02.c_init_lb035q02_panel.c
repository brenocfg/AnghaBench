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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lb035q02_write_reg (struct spi_device*,int,int) ; 

__attribute__((used)) static void init_lb035q02_panel(struct spi_device *spi)
{
	/* Init sequence from page 28 of the lb035q02 spec */
	lb035q02_write_reg(spi, 0x01, 0x6300);
	lb035q02_write_reg(spi, 0x02, 0x0200);
	lb035q02_write_reg(spi, 0x03, 0x0177);
	lb035q02_write_reg(spi, 0x04, 0x04c7);
	lb035q02_write_reg(spi, 0x05, 0xffc0);
	lb035q02_write_reg(spi, 0x06, 0xe806);
	lb035q02_write_reg(spi, 0x0a, 0x4008);
	lb035q02_write_reg(spi, 0x0b, 0x0000);
	lb035q02_write_reg(spi, 0x0d, 0x0030);
	lb035q02_write_reg(spi, 0x0e, 0x2800);
	lb035q02_write_reg(spi, 0x0f, 0x0000);
	lb035q02_write_reg(spi, 0x16, 0x9f80);
	lb035q02_write_reg(spi, 0x17, 0x0a0f);
	lb035q02_write_reg(spi, 0x1e, 0x00c1);
	lb035q02_write_reg(spi, 0x30, 0x0300);
	lb035q02_write_reg(spi, 0x31, 0x0007);
	lb035q02_write_reg(spi, 0x32, 0x0000);
	lb035q02_write_reg(spi, 0x33, 0x0000);
	lb035q02_write_reg(spi, 0x34, 0x0707);
	lb035q02_write_reg(spi, 0x35, 0x0004);
	lb035q02_write_reg(spi, 0x36, 0x0302);
	lb035q02_write_reg(spi, 0x37, 0x0202);
	lb035q02_write_reg(spi, 0x3a, 0x0a0d);
	lb035q02_write_reg(spi, 0x3b, 0x0806);
}