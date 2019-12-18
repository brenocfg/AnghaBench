#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct pm8xxx_xoadc {TYPE_1__* graph; int /*<<< orphan*/  dev; } ;
struct pm8xxx_chan_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ dy; scalar_t__ gnd; void* dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMUX_RSV4 ; 
 int /*<<< orphan*/  AMUX_RSV5 ; 
 int ENODEV ; 
 int /*<<< orphan*/  PM8XXX_CHANNEL_125V ; 
 int /*<<< orphan*/  PM8XXX_CHANNEL_INTERNAL ; 
 int /*<<< orphan*/  PM8XXX_CHANNEL_MUXOFF ; 
 void* VADC_ABSOLUTE_RANGE_UV ; 
 size_t VADC_CALIB_ABSOLUTE ; 
 size_t VADC_CALIB_RATIOMETRIC ; 
 void* VADC_RATIOMETRIC_RANGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,void*,scalar_t__) ; 
 struct pm8xxx_chan_info* pm8xxx_get_channel (struct pm8xxx_xoadc*,int /*<<< orphan*/ ) ; 
 int pm8xxx_read_channel (struct pm8xxx_xoadc*,struct pm8xxx_chan_info const*,scalar_t__*) ; 
 int pm8xxx_read_channel_rsv (struct pm8xxx_xoadc*,struct pm8xxx_chan_info const*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int pm8xxx_calibrate_device(struct pm8xxx_xoadc *adc)
{
	const struct pm8xxx_chan_info *ch;
	u16 read_1250v;
	u16 read_0625v;
	u16 read_nomux_rsv5;
	u16 read_nomux_rsv4;
	int ret;

	adc->graph[VADC_CALIB_ABSOLUTE].dx = VADC_ABSOLUTE_RANGE_UV;
	adc->graph[VADC_CALIB_RATIOMETRIC].dx = VADC_RATIOMETRIC_RANGE;

	/* Common reference channel calibration */
	ch = pm8xxx_get_channel(adc, PM8XXX_CHANNEL_125V);
	if (!ch)
		return -ENODEV;
	ret = pm8xxx_read_channel(adc, ch, &read_1250v);
	if (ret) {
		dev_err(adc->dev, "could not read 1.25V reference channel\n");
		return -ENODEV;
	}
	ch = pm8xxx_get_channel(adc, PM8XXX_CHANNEL_INTERNAL);
	if (!ch)
		return -ENODEV;
	ret = pm8xxx_read_channel(adc, ch, &read_0625v);
	if (ret) {
		dev_err(adc->dev, "could not read 0.625V reference channel\n");
		return -ENODEV;
	}
	if (read_1250v == read_0625v) {
		dev_err(adc->dev, "read same ADC code for 1.25V and 0.625V\n");
		return -ENODEV;
	}

	adc->graph[VADC_CALIB_ABSOLUTE].dy = read_1250v - read_0625v;
	adc->graph[VADC_CALIB_ABSOLUTE].gnd = read_0625v;

	dev_info(adc->dev, "absolute calibration dx = %d uV, dy = %d units\n",
		 VADC_ABSOLUTE_RANGE_UV, adc->graph[VADC_CALIB_ABSOLUTE].dy);

	/* Ratiometric calibration */
	ch = pm8xxx_get_channel(adc, PM8XXX_CHANNEL_MUXOFF);
	if (!ch)
		return -ENODEV;
	ret = pm8xxx_read_channel_rsv(adc, ch, AMUX_RSV5,
				      &read_nomux_rsv5, true);
	if (ret) {
		dev_err(adc->dev, "could not read MUXOFF reference channel\n");
		return -ENODEV;
	}
	ret = pm8xxx_read_channel_rsv(adc, ch, AMUX_RSV4,
				      &read_nomux_rsv4, true);
	if (ret) {
		dev_err(adc->dev, "could not read MUXOFF reference channel\n");
		return -ENODEV;
	}
	adc->graph[VADC_CALIB_RATIOMETRIC].dy =
		read_nomux_rsv5 - read_nomux_rsv4;
	adc->graph[VADC_CALIB_RATIOMETRIC].gnd = read_nomux_rsv4;

	dev_info(adc->dev, "ratiometric calibration dx = %d, dy = %d units\n",
		 VADC_RATIOMETRIC_RANGE,
		 adc->graph[VADC_CALIB_RATIOMETRIC].dy);

	return 0;
}