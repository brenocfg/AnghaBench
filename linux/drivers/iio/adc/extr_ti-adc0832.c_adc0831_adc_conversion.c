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
struct adc0832 {int* rx_buf; struct spi_device* spi; } ;

/* Variables and functions */
 int spi_read (struct spi_device*,int**,int) ; 

__attribute__((used)) static int adc0831_adc_conversion(struct adc0832 *adc)
{
	struct spi_device *spi = adc->spi;
	int ret;

	ret = spi_read(spi, &adc->rx_buf, 2);
	if (ret)
		return ret;

	/*
	 * Skip TRI-STATE and a leading zero
	 */
	return (adc->rx_buf[0] << 2 & 0xff) | (adc->rx_buf[1] >> 6);
}