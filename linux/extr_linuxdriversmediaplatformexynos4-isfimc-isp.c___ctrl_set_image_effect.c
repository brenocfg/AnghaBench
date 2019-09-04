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
struct fimc_is {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const**) ; 
 int EINVAL ; 
#define  ISP_IMAGE_EFFECT_DISABLE 136 
#define  ISP_IMAGE_EFFECT_MONOCHROME 135 
#define  ISP_IMAGE_EFFECT_NEGATIVE_COLOR 134 
#define  ISP_IMAGE_EFFECT_NEGATIVE_MONO 133 
#define  ISP_IMAGE_EFFECT_SEPIA 132 
#define  V4L2_COLORFX_BW 131 
#define  V4L2_COLORFX_NEGATIVE 130 
#define  V4L2_COLORFX_NONE 129 
#define  V4L2_COLORFX_SEPIA 128 
 int /*<<< orphan*/  __is_set_isp_effect (struct fimc_is*,int const) ; 

__attribute__((used)) static int __ctrl_set_image_effect(struct fimc_is *is, int value)
{
	static const u8 effects[][2] = {
		{ V4L2_COLORFX_NONE,	 ISP_IMAGE_EFFECT_DISABLE },
		{ V4L2_COLORFX_BW,	 ISP_IMAGE_EFFECT_MONOCHROME },
		{ V4L2_COLORFX_SEPIA,	 ISP_IMAGE_EFFECT_SEPIA },
		{ V4L2_COLORFX_NEGATIVE, ISP_IMAGE_EFFECT_NEGATIVE_MONO },
		{ 16 /* TODO */,	 ISP_IMAGE_EFFECT_NEGATIVE_COLOR },
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(effects); i++) {
		if (effects[i][0] != value)
			continue;

		__is_set_isp_effect(is, effects[i][1]);
		return 0;
	}

	return -EINVAL;
}