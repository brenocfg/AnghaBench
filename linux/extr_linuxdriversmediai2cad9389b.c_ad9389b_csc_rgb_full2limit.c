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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad9389b_csc_coeff (struct v4l2_subdev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ad9389b_csc_conversion_mode (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad9389b_wr_and_or (struct v4l2_subdev*,int,int,int) ; 

__attribute__((used)) static void ad9389b_csc_rgb_full2limit(struct v4l2_subdev *sd, bool enable)
{
	if (enable) {
		u8 csc_mode = 0;

		ad9389b_csc_conversion_mode(sd, csc_mode);
		ad9389b_csc_coeff(sd,
				  4096-564, 0, 0, 256,
				  0, 4096-564, 0, 256,
				  0, 0, 4096-564, 256);
		/* enable CSC */
		ad9389b_wr_and_or(sd, 0x3b, 0xfe, 0x1);
		/* AVI infoframe: Limited range RGB (16-235) */
		ad9389b_wr_and_or(sd, 0xcd, 0xf9, 0x02);
	} else {
		/* disable CSC */
		ad9389b_wr_and_or(sd, 0x3b, 0xfe, 0x0);
		/* AVI infoframe: Full range RGB (0-255) */
		ad9389b_wr_and_or(sd, 0xcd, 0xf9, 0x04);
	}
}