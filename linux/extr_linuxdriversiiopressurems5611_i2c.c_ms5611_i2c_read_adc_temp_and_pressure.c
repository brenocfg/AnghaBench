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
struct ms5611_state {int /*<<< orphan*/  client; struct ms5611_osr* pressure_osr; struct ms5611_osr* temp_osr; } ;
struct ms5611_osr {unsigned long conv_usec; int /*<<< orphan*/  cmd; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ms5611_state* iio_priv (int /*<<< orphan*/ ) ; 
 int ms5611_i2c_read_adc (struct ms5611_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (unsigned long,unsigned long) ; 

__attribute__((used)) static int ms5611_i2c_read_adc_temp_and_pressure(struct device *dev,
						 s32 *temp, s32 *pressure)
{
	int ret;
	struct ms5611_state *st = iio_priv(dev_to_iio_dev(dev));
	const struct ms5611_osr *osr = st->temp_osr;

	ret = i2c_smbus_write_byte(st->client, osr->cmd);
	if (ret < 0)
		return ret;

	usleep_range(osr->conv_usec, osr->conv_usec + (osr->conv_usec / 10UL));
	ret = ms5611_i2c_read_adc(st, temp);
	if (ret < 0)
		return ret;

	osr = st->pressure_osr;
	ret = i2c_smbus_write_byte(st->client, osr->cmd);
	if (ret < 0)
		return ret;

	usleep_range(osr->conv_usec, osr->conv_usec + (osr->conv_usec / 10UL));
	return ms5611_i2c_read_adc(st, pressure);
}