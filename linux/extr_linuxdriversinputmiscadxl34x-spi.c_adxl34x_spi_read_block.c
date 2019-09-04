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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 unsigned char ADXL34X_READMB_CMD (unsigned char) ; 
 scalar_t__ spi_write_then_read (struct spi_device*,unsigned char*,int,void*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int adxl34x_spi_read_block(struct device *dev,
				  unsigned char reg, int count,
				  void *buf)
{
	struct spi_device *spi = to_spi_device(dev);
	ssize_t status;

	reg = ADXL34X_READMB_CMD(reg);
	status = spi_write_then_read(spi, &reg, 1, buf, count);

	return (status < 0) ? status : 0;
}