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
struct spi_transfer {int len; int delay_usecs; int cs_change; int* rx_buf; } ;
struct spi_device {int dummy; } ;
struct max1118 {int data; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct max1118* iio_priv (struct iio_dev*) ; 
 struct iio_dev* spi_get_drvdata (struct spi_device*) ; 
 int spi_sync_transfer (struct spi_device*,struct spi_transfer*,int) ; 

__attribute__((used)) static int max1118_read(struct spi_device *spi, int channel)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct max1118 *adc = iio_priv(indio_dev);
	struct spi_transfer xfers[] = {
		/*
		 * To select CH1 for conversion, CNVST pin must be brought high
		 * and low for a second time.
		 */
		{
			.len = 0,
			.delay_usecs = 1,	/* > CNVST Low Time 100 ns */
			.cs_change = 1,
		},
		/*
		 * The acquisition interval begins with the falling edge of
		 * CNVST.  The total acquisition and conversion process takes
		 * <7.5us.
		 */
		{
			.len = 0,
			.delay_usecs = 8,
		},
		{
			.rx_buf = &adc->data,
			.len = 1,
		},
	};
	int ret;

	if (channel == 0)
		ret = spi_sync_transfer(spi, xfers + 1, 2);
	else
		ret = spi_sync_transfer(spi, xfers, 3);

	if (ret)
		return ret;

	return adc->data;
}