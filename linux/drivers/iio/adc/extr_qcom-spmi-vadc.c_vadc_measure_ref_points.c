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
struct vadc_priv {int /*<<< orphan*/  dev; TYPE_1__* graph; } ;
struct vadc_channel_prop {int dummy; } ;
struct TYPE_2__ {scalar_t__ gnd; scalar_t__ dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VADC_ABSOLUTE_RANGE_UV ; 
 size_t VADC_CALIB_ABSOLUTE ; 
 size_t VADC_CALIB_RATIOMETRIC ; 
 int /*<<< orphan*/  VADC_GND_REF ; 
 int /*<<< orphan*/  VADC_RATIOMETRIC_RANGE ; 
 int /*<<< orphan*/  VADC_REF_1250MV ; 
 int /*<<< orphan*/  VADC_REF_625MV ; 
 int /*<<< orphan*/  VADC_SPARE1 ; 
 int /*<<< orphan*/  VADC_VDD_VADC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int vadc_do_conversion (struct vadc_priv*,struct vadc_channel_prop*,scalar_t__*) ; 
 struct vadc_channel_prop* vadc_get_channel (struct vadc_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vadc_measure_ref_points(struct vadc_priv *vadc)
{
	struct vadc_channel_prop *prop;
	u16 read_1, read_2;
	int ret;

	vadc->graph[VADC_CALIB_RATIOMETRIC].dx = VADC_RATIOMETRIC_RANGE;
	vadc->graph[VADC_CALIB_ABSOLUTE].dx = VADC_ABSOLUTE_RANGE_UV;

	prop = vadc_get_channel(vadc, VADC_REF_1250MV);
	ret = vadc_do_conversion(vadc, prop, &read_1);
	if (ret)
		goto err;

	/* Try with buffered 625mV channel first */
	prop = vadc_get_channel(vadc, VADC_SPARE1);
	if (!prop)
		prop = vadc_get_channel(vadc, VADC_REF_625MV);

	ret = vadc_do_conversion(vadc, prop, &read_2);
	if (ret)
		goto err;

	if (read_1 == read_2) {
		ret = -EINVAL;
		goto err;
	}

	vadc->graph[VADC_CALIB_ABSOLUTE].dy = read_1 - read_2;
	vadc->graph[VADC_CALIB_ABSOLUTE].gnd = read_2;

	/* Ratiometric calibration */
	prop = vadc_get_channel(vadc, VADC_VDD_VADC);
	ret = vadc_do_conversion(vadc, prop, &read_1);
	if (ret)
		goto err;

	prop = vadc_get_channel(vadc, VADC_GND_REF);
	ret = vadc_do_conversion(vadc, prop, &read_2);
	if (ret)
		goto err;

	if (read_1 == read_2) {
		ret = -EINVAL;
		goto err;
	}

	vadc->graph[VADC_CALIB_RATIOMETRIC].dy = read_1 - read_2;
	vadc->graph[VADC_CALIB_RATIOMETRIC].gnd = read_2;
err:
	if (ret)
		dev_err(vadc->dev, "measure reference points failed\n");

	return ret;
}