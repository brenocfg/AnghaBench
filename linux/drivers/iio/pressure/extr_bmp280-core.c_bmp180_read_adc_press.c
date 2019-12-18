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
struct bmp280_data {int oversampling_press; int /*<<< orphan*/  regmap; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BMP180_MEAS_PRESS_X (int) ; 
 int /*<<< orphan*/  BMP180_REG_OUT_MSB ; 
 int be32_to_cpu (scalar_t__) ; 
 int bmp180_measure (struct bmp280_data*,int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int bmp180_read_adc_press(struct bmp280_data *data, int *val)
{
	int ret;
	__be32 tmp = 0;
	u8 oss = data->oversampling_press;

	ret = bmp180_measure(data, BMP180_MEAS_PRESS_X(oss));
	if (ret)
		return ret;

	ret = regmap_bulk_read(data->regmap, BMP180_REG_OUT_MSB, (u8 *)&tmp, 3);
	if (ret)
		return ret;

	*val = (be32_to_cpu(tmp) >> 8) >> (8 - oss);

	return 0;
}