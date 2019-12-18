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
struct ad_sigma_delta {int dummy; } ;
struct ad7780_state {int /*<<< orphan*/  powerdown_gpio; } ;
typedef  enum ad_sigma_delta_mode { ____Placeholder_ad_sigma_delta_mode } ad_sigma_delta_mode ;

/* Variables and functions */
#define  AD_SD_MODE_CONTINUOUS 129 
#define  AD_SD_MODE_SINGLE 128 
 struct ad7780_state* ad_sigma_delta_to_ad7780 (struct ad_sigma_delta*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ad7780_set_mode(struct ad_sigma_delta *sigma_delta,
			   enum ad_sigma_delta_mode mode)
{
	struct ad7780_state *st = ad_sigma_delta_to_ad7780(sigma_delta);
	unsigned int val;

	switch (mode) {
	case AD_SD_MODE_SINGLE:
	case AD_SD_MODE_CONTINUOUS:
		val = 1;
		break;
	default:
		val = 0;
		break;
	}

	gpiod_set_value(st->powerdown_gpio, val);

	return 0;
}