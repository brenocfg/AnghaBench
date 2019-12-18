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
 int /*<<< orphan*/  adv7511_csc_coeff (struct v4l2_subdev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  adv7511_csc_conversion_mode (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv7511_wr_and_or (struct v4l2_subdev*,int,int,int) ; 

__attribute__((used)) static void adv7511_csc_rgb_full2limit(struct v4l2_subdev *sd, bool enable)
{
	if (enable) {
		u8 csc_mode = 0;
		adv7511_csc_conversion_mode(sd, csc_mode);
		adv7511_csc_coeff(sd,
				  4096-564, 0, 0, 256,
				  0, 4096-564, 0, 256,
				  0, 0, 4096-564, 256);
		/* enable CSC */
		adv7511_wr_and_or(sd, 0x18, 0x7f, 0x80);
		/* AVI infoframe: Limited range RGB (16-235) */
		adv7511_wr_and_or(sd, 0x57, 0xf3, 0x04);
	} else {
		/* disable CSC */
		adv7511_wr_and_or(sd, 0x18, 0x7f, 0x0);
		/* AVI infoframe: Full range RGB (0-255) */
		adv7511_wr_and_or(sd, 0x57, 0xf3, 0x08);
	}
}