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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned char ADXL34X_READCMD (unsigned char) ; 
 int spi_w8r8 (struct spi_device*,unsigned char) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int adxl34x_spi_read(struct device *dev, unsigned char reg)
{
	struct spi_device *spi = to_spi_device(dev);
	unsigned char cmd;

	cmd = ADXL34X_READCMD(reg);

	return spi_w8r8(spi, cmd);
}