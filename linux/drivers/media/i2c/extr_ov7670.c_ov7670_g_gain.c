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
typedef  unsigned char __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  REG_GAIN ; 
 int ov7670_read (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int ov7670_g_gain(struct v4l2_subdev *sd, __s32 *value)
{
	int ret;
	unsigned char gain;

	ret = ov7670_read(sd, REG_GAIN, &gain);
	*value = gain;
	return ret;
}