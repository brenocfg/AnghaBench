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
struct ms5611_state {int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int MS5611_READ_ADC ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct ms5611_state* iio_priv (int /*<<< orphan*/ ) ; 
 int spi_write_then_read (int /*<<< orphan*/ ,int*,int,int*,int) ; 

__attribute__((used)) static int ms5611_spi_read_adc(struct device *dev, s32 *val)
{
	int ret;
	u8 buf[3] = { MS5611_READ_ADC };
	struct ms5611_state *st = iio_priv(dev_to_iio_dev(dev));

	ret = spi_write_then_read(st->client, buf, 1, buf, 3);
	if (ret < 0)
		return ret;

	*val = (buf[0] << 16) | (buf[1] << 8) | buf[2];

	return 0;
}