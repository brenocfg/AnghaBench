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
typedef  int uint32_t ;
struct regamma_ramp {unsigned short* gamma; } ;
struct pwl_float_data {void* b; void* g; void* r; } ;
struct dividers {int /*<<< orphan*/  divider3; int /*<<< orphan*/  divider2; int /*<<< orphan*/  divider1; } ;

/* Variables and functions */
 int GAMMA_RGB_256_ENTRIES ; 
 void* dc_fixpt_from_fraction (unsigned short,unsigned short) ; 
 void* dc_fixpt_mul (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scale_user_regamma_ramp(struct pwl_float_data *pwl_rgb,
		const struct regamma_ramp *ramp,
		struct dividers dividers)
{
	unsigned short max_driver = 0xFFFF;
	unsigned short max_os = 0xFF00;
	unsigned short scaler = max_os;
	uint32_t i;
	struct pwl_float_data *rgb = pwl_rgb;
	struct pwl_float_data *rgb_last = rgb + GAMMA_RGB_256_ENTRIES - 1;

	i = 0;
	do {
		if (ramp->gamma[i] > max_os ||
				ramp->gamma[i + 256] > max_os ||
				ramp->gamma[i + 512] > max_os) {
			scaler = max_driver;
			break;
		}
		i++;
	} while (i != GAMMA_RGB_256_ENTRIES);

	i = 0;
	do {
		rgb->r = dc_fixpt_from_fraction(
				ramp->gamma[i], scaler);
		rgb->g = dc_fixpt_from_fraction(
				ramp->gamma[i + 256], scaler);
		rgb->b = dc_fixpt_from_fraction(
				ramp->gamma[i + 512], scaler);

		++rgb;
		++i;
	} while (i != GAMMA_RGB_256_ENTRIES);

	rgb->r = dc_fixpt_mul(rgb_last->r,
			dividers.divider1);
	rgb->g = dc_fixpt_mul(rgb_last->g,
			dividers.divider1);
	rgb->b = dc_fixpt_mul(rgb_last->b,
			dividers.divider1);

	++rgb;

	rgb->r = dc_fixpt_mul(rgb_last->r,
			dividers.divider2);
	rgb->g = dc_fixpt_mul(rgb_last->g,
			dividers.divider2);
	rgb->b = dc_fixpt_mul(rgb_last->b,
			dividers.divider2);

	++rgb;

	rgb->r = dc_fixpt_mul(rgb_last->r,
			dividers.divider3);
	rgb->g = dc_fixpt_mul(rgb_last->g,
			dividers.divider3);
	rgb->b = dc_fixpt_mul(rgb_last->b,
			dividers.divider3);
}