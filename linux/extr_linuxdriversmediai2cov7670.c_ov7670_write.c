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
struct ov7670_info {scalar_t__ use_smbus; } ;

/* Variables and functions */
 int ov7670_write_i2c (struct v4l2_subdev*,unsigned char,unsigned char) ; 
 int ov7670_write_smbus (struct v4l2_subdev*,unsigned char,unsigned char) ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7670_write(struct v4l2_subdev *sd, unsigned char reg,
		unsigned char value)
{
	struct ov7670_info *info = to_state(sd);
	if (info->use_smbus)
		return ov7670_write_smbus(sd, reg, value);
	else
		return ov7670_write_i2c(sd, reg, value);
}