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
typedef  int u32 ;
struct bmp280_data {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IIO_VAL_FRACTIONAL ; 
 int bmp180_compensate_press (struct bmp280_data*,int /*<<< orphan*/ ) ; 
 int bmp180_read_adc_press (struct bmp280_data*,int /*<<< orphan*/ *) ; 
 int bmp180_read_temp (struct bmp280_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmp180_read_press(struct bmp280_data *data,
			     int *val, int *val2)
{
	int ret;
	s32 adc_press;
	u32 comp_press;

	/* Read and compensate temperature so we get a reading of t_fine. */
	ret = bmp180_read_temp(data, NULL);
	if (ret)
		return ret;

	ret = bmp180_read_adc_press(data, &adc_press);
	if (ret)
		return ret;

	comp_press = bmp180_compensate_press(data, adc_press);

	*val = comp_press;
	*val2 = 1000;

	return IIO_VAL_FRACTIONAL;
}