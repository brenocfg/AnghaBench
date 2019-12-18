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
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
#define  V4L2_COLORFX_BW 132 
#define  V4L2_COLORFX_NEGATIVE 131 
#define  V4L2_COLORFX_NONE 130 
#define  V4L2_COLORFX_SEPIA 129 
#define  V4L2_COLORFX_SKETCH 128 
 int /*<<< orphan*/ * effects_table ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void seteffect(struct gspca_dev *gspca_dev, s32 val)
{
	int idx = 0;

	switch (val) {
	case V4L2_COLORFX_NONE:
		break;
	case V4L2_COLORFX_BW:
		idx = 2;
		break;
	case V4L2_COLORFX_SEPIA:
		idx = 3;
		break;
	case V4L2_COLORFX_SKETCH:
		idx = 4;
		break;
	case V4L2_COLORFX_NEGATIVE:
		idx = 6;
		break;
	default:
		break;
	}

	reg_w_buf(gspca_dev, effects_table[idx],
				sizeof effects_table[0]);

	if (val == V4L2_COLORFX_SKETCH)
		reg_w(gspca_dev, 0x4aa6);
	else
		reg_w(gspca_dev, 0xfaa6);
}