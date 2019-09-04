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
 int /*<<< orphan*/  hdmi_write (struct v4l2_subdev*,int,int) ; 

__attribute__((used)) static void adv7611_set_termination(struct v4l2_subdev *sd, bool enable)
{
	hdmi_write(sd, 0x83, enable ? 0xfe : 0xff);
}