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
typedef  int u8 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int repaper_spi_transfer (struct spi_device*,int,int*,int*,int) ; 

__attribute__((used)) static int repaper_read_val(struct spi_device *spi, u8 reg)
{
	int ret;
	u8 val;

	ret = repaper_spi_transfer(spi, 0x70, &reg, NULL, 1);
	if (ret)
		return ret;

	ret = repaper_spi_transfer(spi, 0x73, NULL, &val, 1);

	return ret ? ret : val;
}