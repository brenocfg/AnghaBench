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
struct ad7791_state {int /*<<< orphan*/  mode; } ;
typedef  enum ad_sigma_delta_mode { ____Placeholder_ad_sigma_delta_mode } ad_sigma_delta_mode ;

/* Variables and functions */
 int AD7791_MODE_CONTINUOUS ; 
 int AD7791_MODE_POWERDOWN ; 
 int /*<<< orphan*/  AD7791_MODE_SEL (int) ; 
 int /*<<< orphan*/  AD7791_MODE_SEL_MASK ; 
 int AD7791_MODE_SINGLE ; 
 int /*<<< orphan*/  AD7791_REG_MODE ; 
#define  AD_SD_MODE_CONTINUOUS 131 
#define  AD_SD_MODE_IDLE 130 
#define  AD_SD_MODE_POWERDOWN 129 
#define  AD_SD_MODE_SINGLE 128 
 int ad_sd_write_reg (struct ad_sigma_delta*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ad7791_state* ad_sigma_delta_to_ad7791 (struct ad_sigma_delta*) ; 

__attribute__((used)) static int ad7791_set_mode(struct ad_sigma_delta *sd,
	enum ad_sigma_delta_mode mode)
{
	struct ad7791_state *st = ad_sigma_delta_to_ad7791(sd);

	switch (mode) {
	case AD_SD_MODE_CONTINUOUS:
		mode = AD7791_MODE_CONTINUOUS;
		break;
	case AD_SD_MODE_SINGLE:
		mode = AD7791_MODE_SINGLE;
		break;
	case AD_SD_MODE_IDLE:
	case AD_SD_MODE_POWERDOWN:
		mode = AD7791_MODE_POWERDOWN;
		break;
	}

	st->mode &= ~AD7791_MODE_SEL_MASK;
	st->mode |= AD7791_MODE_SEL(mode);

	return ad_sd_write_reg(sd, AD7791_REG_MODE, sizeof(st->mode), st->mode);
}