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
 int ENODEV ; 
 int /*<<< orphan*/  REG_MIDH ; 
 int /*<<< orphan*/  REG_MIDL ; 
 int /*<<< orphan*/  REG_PID ; 
 int /*<<< orphan*/  REG_VER ; 
 int ov7670_init (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int ov7670_read (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int ov7670_detect(struct v4l2_subdev *sd)
{
	unsigned char v;
	int ret;

	ret = ov7670_init(sd, 0);
	if (ret < 0)
		return ret;
	ret = ov7670_read(sd, REG_MIDH, &v);
	if (ret < 0)
		return ret;
	if (v != 0x7f) /* OV manuf. id. */
		return -ENODEV;
	ret = ov7670_read(sd, REG_MIDL, &v);
	if (ret < 0)
		return ret;
	if (v != 0xa2)
		return -ENODEV;
	/*
	 * OK, we know we have an OmniVision chip...but which one?
	 */
	ret = ov7670_read(sd, REG_PID, &v);
	if (ret < 0)
		return ret;
	if (v != 0x76)  /* PID + VER = 0x76 / 0x73 */
		return -ENODEV;
	ret = ov7670_read(sd, REG_VER, &v);
	if (ret < 0)
		return ret;
	if (v != 0x73)  /* PID + VER = 0x76 / 0x73 */
		return -ENODEV;
	return 0;
}