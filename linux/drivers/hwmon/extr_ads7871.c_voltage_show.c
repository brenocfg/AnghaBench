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
typedef  int uint8_t ;
struct spi_device {int dummy; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ads7871_data {struct spi_device* spi; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int MUX_CNV_BM ; 
 int MUX_CNV_BV ; 
 int MUX_M3_BM ; 
 int /*<<< orphan*/  REG_GAIN_MUX ; 
 int /*<<< orphan*/  REG_LS_BYTE ; 
 int ads7871_read_reg16 (struct spi_device*,int /*<<< orphan*/ ) ; 
 int ads7871_read_reg8 (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ads7871_write_reg8 (struct spi_device*,int /*<<< orphan*/ ,int) ; 
 struct ads7871_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t voltage_show(struct device *dev, struct device_attribute *da,
			    char *buf)
{
	struct ads7871_data *pdata = dev_get_drvdata(dev);
	struct spi_device *spi = pdata->spi;
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	int ret, val, i = 0;
	uint8_t channel, mux_cnv;

	channel = attr->index;
	/*
	 * TODO: add support for conversions
	 * other than single ended with a gain of 1
	 */
	/*MUX_M3_BM forces single ended*/
	/*This is also where the gain of the PGA would be set*/
	ads7871_write_reg8(spi, REG_GAIN_MUX,
		(MUX_CNV_BM | MUX_M3_BM | channel));

	ret = ads7871_read_reg8(spi, REG_GAIN_MUX);
	mux_cnv = ((ret & MUX_CNV_BM) >> MUX_CNV_BV);
	/*
	 * on 400MHz arm9 platform the conversion
	 * is already done when we do this test
	 */
	while ((i < 2) && mux_cnv) {
		i++;
		ret = ads7871_read_reg8(spi, REG_GAIN_MUX);
		mux_cnv = ((ret & MUX_CNV_BM) >> MUX_CNV_BV);
		msleep_interruptible(1);
	}

	if (mux_cnv == 0) {
		val = ads7871_read_reg16(spi, REG_LS_BYTE);
		/*result in volts*10000 = (val/8192)*2.5*10000*/
		val = ((val >> 2) * 25000) / 8192;
		return sprintf(buf, "%d\n", val);
	} else {
		return -1;
	}
}