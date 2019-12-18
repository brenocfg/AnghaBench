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
typedef  int u16 ;
struct mt9m032 {int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  MT9M032_GAIN_ALL ; 
 int MT9M032_GAIN_AMUL_SHIFT ; 
 int MT9M032_GAIN_ANALOG_MASK ; 
 int MT9M032_GAIN_DIGITAL_MASK ; 
 int MT9M032_GAIN_DIGITAL_SHIFT ; 
 int mt9m032_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m032_set_gain(struct mt9m032 *sensor, s32 val)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	int digital_gain_val;	/* in 1/8th (0..127) */
	int analog_mul;		/* 0 or 1 */
	int analog_gain_val;	/* in 1/16th. (0..63) */
	u16 reg_val;

	digital_gain_val = 51; /* from setup example */

	if (val < 63) {
		analog_mul = 0;
		analog_gain_val = val;
	} else {
		analog_mul = 1;
		analog_gain_val = val / 2;
	}

	/* a_gain = (1 + analog_mul) + (analog_gain_val + 1) / 16 */
	/* overall_gain = a_gain * (1 + digital_gain_val / 8) */

	reg_val = ((digital_gain_val & MT9M032_GAIN_DIGITAL_MASK)
		   << MT9M032_GAIN_DIGITAL_SHIFT)
		| ((analog_mul & 1) << MT9M032_GAIN_AMUL_SHIFT)
		| (analog_gain_val & MT9M032_GAIN_ANALOG_MASK);

	return mt9m032_write(client, MT9M032_GAIN_ALL, reg_val);
}