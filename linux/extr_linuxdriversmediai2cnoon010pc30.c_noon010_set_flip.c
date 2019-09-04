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
struct noon010_info {int hflip; int vflip; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDO_CTL_REG (int) ; 
 int cam_i2c_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int cam_i2c_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct noon010_info* to_noon010 (struct v4l2_subdev*) ; 

__attribute__((used)) static int noon010_set_flip(struct v4l2_subdev *sd, int hflip, int vflip)
{
	struct noon010_info *info = to_noon010(sd);
	int reg, ret;

	reg = cam_i2c_read(sd, VDO_CTL_REG(1));
	if (reg < 0)
		return reg;

	reg &= 0x7C;
	if (hflip)
		reg |= 0x01;
	if (vflip)
		reg |= 0x02;

	ret = cam_i2c_write(sd, VDO_CTL_REG(1), reg | 0x80);
	if (!ret) {
		info->hflip = hflip;
		info->vflip = vflip;
	}
	return ret;
}