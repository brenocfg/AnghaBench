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
struct ina2xx_data {TYPE_1__* config; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  calibration_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  INA2XX_CALIBRATION ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ina2xx_calibrate(struct ina2xx_data *data)
{
	return regmap_write(data->regmap, INA2XX_CALIBRATION,
			    data->config->calibration_value);
}