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
 unsigned char COM8_AGC ; 
 int /*<<< orphan*/  REG_COM8 ; 
 int ov7670_read (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char*) ; 
 int ov7670_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int ov7670_s_autogain(struct v4l2_subdev *sd, int value)
{
	int ret;
	unsigned char com8;

	ret = ov7670_read(sd, REG_COM8, &com8);
	if (ret == 0) {
		if (value)
			com8 |= COM8_AGC;
		else
			com8 &= ~COM8_AGC;
		ret = ov7670_write(sd, REG_COM8, com8);
	}
	return ret;
}