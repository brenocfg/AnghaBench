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
struct alps_data {int x_max; int y_max; int x_res; int y_res; int /*<<< orphan*/  dev_id; } ;

/* Variables and functions */
 scalar_t__ IS_SS4PLUS_DEV (int /*<<< orphan*/ ) ; 
 int SS4PLUS_COUNT_PER_ELECTRODE ; 
 unsigned char SS4PLUS_MIN_PITCH_MM ; 
 unsigned char SS4PLUS_NUMSENSOR_XOFFSET ; 
 unsigned char SS4PLUS_NUMSENSOR_YOFFSET ; 
 int SS4_COUNT_PER_ELECTRODE ; 
 unsigned char SS4_MIN_PITCH_MM ; 
 unsigned char SS4_NUMSENSOR_XOFFSET ; 
 unsigned char SS4_NUMSENSOR_YOFFSET ; 

__attribute__((used)) static int alps_update_device_area_ss4_v2(unsigned char otp[][4],
					  struct alps_data *priv)
{
	int num_x_electrode;
	int num_y_electrode;
	int x_pitch, y_pitch, x_phys, y_phys;

	if (IS_SS4PLUS_DEV(priv->dev_id)) {
		num_x_electrode =
			SS4PLUS_NUMSENSOR_XOFFSET + (otp[0][2] & 0x0F);
		num_y_electrode =
			SS4PLUS_NUMSENSOR_YOFFSET + ((otp[0][2] >> 4) & 0x0F);

		priv->x_max =
			(num_x_electrode - 1) * SS4PLUS_COUNT_PER_ELECTRODE;
		priv->y_max =
			(num_y_electrode - 1) * SS4PLUS_COUNT_PER_ELECTRODE;

		x_pitch = (otp[0][1] & 0x0F) + SS4PLUS_MIN_PITCH_MM;
		y_pitch = ((otp[0][1] >> 4) & 0x0F) + SS4PLUS_MIN_PITCH_MM;

	} else {
		num_x_electrode =
			SS4_NUMSENSOR_XOFFSET + (otp[1][0] & 0x0F);
		num_y_electrode =
			SS4_NUMSENSOR_YOFFSET + ((otp[1][0] >> 4) & 0x0F);

		priv->x_max =
			(num_x_electrode - 1) * SS4_COUNT_PER_ELECTRODE;
		priv->y_max =
			(num_y_electrode - 1) * SS4_COUNT_PER_ELECTRODE;

		x_pitch = ((otp[1][2] >> 2) & 0x07) + SS4_MIN_PITCH_MM;
		y_pitch = ((otp[1][2] >> 5) & 0x07) + SS4_MIN_PITCH_MM;
	}

	x_phys = x_pitch * (num_x_electrode - 1); /* In 0.1 mm units */
	y_phys = y_pitch * (num_y_electrode - 1); /* In 0.1 mm units */

	priv->x_res = priv->x_max * 10 / x_phys; /* units / mm */
	priv->y_res = priv->y_max * 10 / y_phys; /* units / mm */

	return 0;
}