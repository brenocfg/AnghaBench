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
typedef  scalar_t__ u32 ;
struct tsens_priv {int num_sensors; TYPE_1__* sensor; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int slope; scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ CAL_DEGC_PT1 ; 
 int CAL_DEGC_PT2 ; 
 int SLOPE_DEFAULT ; 
 int SLOPE_FACTOR ; 
 scalar_t__ TWO_PT_CALIB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 

void compute_intercept_slope(struct tsens_priv *priv, u32 *p1,
			     u32 *p2, u32 mode)
{
	int i;
	int num, den;

	for (i = 0; i < priv->num_sensors; i++) {
		dev_dbg(priv->dev,
			"sensor%d - data_point1:%#x data_point2:%#x\n",
			i, p1[i], p2[i]);

		priv->sensor[i].slope = SLOPE_DEFAULT;
		if (mode == TWO_PT_CALIB) {
			/*
			 * slope (m) = adc_code2 - adc_code1 (y2 - y1)/
			 *	temp_120_degc - temp_30_degc (x2 - x1)
			 */
			num = p2[i] - p1[i];
			num *= SLOPE_FACTOR;
			den = CAL_DEGC_PT2 - CAL_DEGC_PT1;
			priv->sensor[i].slope = num / den;
		}

		priv->sensor[i].offset = (p1[i] * SLOPE_FACTOR) -
				(CAL_DEGC_PT1 *
				priv->sensor[i].slope);
		dev_dbg(priv->dev, "offset:%d\n", priv->sensor[i].offset);
	}
}