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
struct cm3605 {int als_max; int /*<<< orphan*/  dev; int /*<<< orphan*/  aout; } ;
typedef  int s64 ;

/* Variables and functions */
 int CM3605_AOUT_MAX_MV ; 
 int /*<<< orphan*/  CM3605_AOUT_TYP_MAX_MV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int div64_s64 (int,int /*<<< orphan*/ ) ; 
 int iio_read_channel_processed (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int cm3605_get_lux(struct cm3605 *cm3605)
{
	int ret, res;
	s64 lux;

	ret = iio_read_channel_processed(cm3605->aout, &res);
	if (ret < 0)
		return ret;

	dev_dbg(cm3605->dev, "read %d mV from ADC\n", res);

	/*
	 * AOUT has an offset of ~30mV then linear at dark
	 * then goes from 2.54 up to 650 LUX yielding 1.55V
	 * (1550 mV) so scale the returned value to this interval
	 * using simple linear interpolation.
	 */
	if (res < 30)
		return 0;
	if (res > CM3605_AOUT_MAX_MV)
		dev_err(cm3605->dev, "device out of range\n");

	/* Remove bias */
	lux = res - 30;

	/* Linear interpolation between 0 and ALS typ max */
	lux *= cm3605->als_max;
	lux = div64_s64(lux, CM3605_AOUT_TYP_MAX_MV);

	return lux;
}