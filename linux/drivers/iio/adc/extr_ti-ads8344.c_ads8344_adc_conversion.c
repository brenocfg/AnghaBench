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
struct ads8344 {int rx_buf; int /*<<< orphan*/  tx_buf; struct spi_device* spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADS8344_CHANNEL (int) ; 
 int /*<<< orphan*/  ADS8344_CLOCK_INTERNAL ; 
 int /*<<< orphan*/  ADS8344_SINGLE_END ; 
 int /*<<< orphan*/  ADS8344_START ; 
 int spi_read (struct spi_device*,int*,int) ; 
 int spi_write (struct spi_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ads8344_adc_conversion(struct ads8344 *adc, int channel,
				  bool differential)
{
	struct spi_device *spi = adc->spi;
	int ret;

	adc->tx_buf = ADS8344_START;
	if (!differential)
		adc->tx_buf |= ADS8344_SINGLE_END;
	adc->tx_buf |= ADS8344_CHANNEL(channel);
	adc->tx_buf |= ADS8344_CLOCK_INTERNAL;

	ret = spi_write(spi, &adc->tx_buf, 1);
	if (ret)
		return ret;

	udelay(9);

	ret = spi_read(spi, &adc->rx_buf, 2);
	if (ret)
		return ret;

	return adc->rx_buf;
}