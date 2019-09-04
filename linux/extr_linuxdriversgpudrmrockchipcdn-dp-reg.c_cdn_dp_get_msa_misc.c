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
typedef  int u32 ;
struct video_info {int color_fmt; int color_depth; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int BT_601 ; 
#define  PXL_RGB 132 
#define  YCBCR_4_2_0 131 
#define  YCBCR_4_2_2 130 
#define  YCBCR_4_4_4 129 
#define  Y_ONLY 128 

__attribute__((used)) static int cdn_dp_get_msa_misc(struct video_info *video,
			       struct drm_display_mode *mode)
{
	u32 msa_misc;
	u8 val[2] = {0};

	switch (video->color_fmt) {
	case PXL_RGB:
	case Y_ONLY:
		val[0] = 0;
		break;
	/* set YUV default color space conversion to BT601 */
	case YCBCR_4_4_4:
		val[0] = 6 + BT_601 * 8;
		break;
	case YCBCR_4_2_2:
		val[0] = 5 + BT_601 * 8;
		break;
	case YCBCR_4_2_0:
		val[0] = 5;
		break;
	};

	switch (video->color_depth) {
	case 6:
		val[1] = 0;
		break;
	case 8:
		val[1] = 1;
		break;
	case 10:
		val[1] = 2;
		break;
	case 12:
		val[1] = 3;
		break;
	case 16:
		val[1] = 4;
		break;
	};

	msa_misc = 2 * val[0] + 32 * val[1] +
		   ((video->color_fmt == Y_ONLY) ? (1 << 14) : 0);

	return msa_misc;
}