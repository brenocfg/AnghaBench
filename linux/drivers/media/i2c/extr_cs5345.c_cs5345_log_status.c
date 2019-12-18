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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int cs5345_read (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int,...) ; 

__attribute__((used)) static int cs5345_log_status(struct v4l2_subdev *sd)
{
	u8 v = cs5345_read(sd, 0x09) & 7;
	u8 m = cs5345_read(sd, 0x04);
	int vol = cs5345_read(sd, 0x08) & 0x3f;

	v4l2_info(sd, "Input:  %d%s\n", v,
			(m & 0x80) ? " (muted)" : "");
	if (vol >= 32)
		vol = vol - 64;
	v4l2_info(sd, "Volume: %d dB\n", vol);
	return 0;
}