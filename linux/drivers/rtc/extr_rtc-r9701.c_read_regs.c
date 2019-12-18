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
typedef  unsigned char u8 ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int spi_write_then_read (struct spi_device*,unsigned char*,int,unsigned char*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int read_regs(struct device *dev, unsigned char *regs, int no_regs)
{
	struct spi_device *spi = to_spi_device(dev);
	u8 txbuf[1], rxbuf[1];
	int k, ret;

	ret = 0;

	for (k = 0; ret == 0 && k < no_regs; k++) {
		txbuf[0] = 0x80 | regs[k];
		ret = spi_write_then_read(spi, txbuf, 1, rxbuf, 1);
		regs[k] = rxbuf[0];
	}

	return ret;
}