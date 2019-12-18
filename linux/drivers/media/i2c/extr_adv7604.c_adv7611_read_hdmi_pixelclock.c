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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int hdmi_read (struct v4l2_subdev*,int) ; 

__attribute__((used)) static unsigned int adv7611_read_hdmi_pixelclock(struct v4l2_subdev *sd)
{
	int a, b;

	a = hdmi_read(sd, 0x51);
	b = hdmi_read(sd, 0x52);
	if (a < 0 || b < 0)
		return 0;
	return ((a << 1) | (b >> 7)) * 1000000 + (b & 0x7f) * 1000000 / 128;
}