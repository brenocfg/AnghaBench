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
typedef  int v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct adv7183 {int std; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7183_IN_CTRL ; 
 int EINVAL ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_NTSC_443 ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_PAL_N ; 
 int V4L2_STD_PAL_Nc ; 
 int V4L2_STD_SECAM ; 
 int adv7183_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv7183_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct adv7183* to_adv7183 (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7183_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct adv7183 *decoder = to_adv7183(sd);
	int reg;

	reg = adv7183_read(sd, ADV7183_IN_CTRL) & 0xF;
	if (std == V4L2_STD_PAL_60)
		reg |= 0x60;
	else if (std == V4L2_STD_NTSC_443)
		reg |= 0x70;
	else if (std == V4L2_STD_PAL_N)
		reg |= 0x90;
	else if (std == V4L2_STD_PAL_M)
		reg |= 0xA0;
	else if (std == V4L2_STD_PAL_Nc)
		reg |= 0xC0;
	else if (std & V4L2_STD_PAL)
		reg |= 0x80;
	else if (std & V4L2_STD_NTSC)
		reg |= 0x50;
	else if (std & V4L2_STD_SECAM)
		reg |= 0xE0;
	else
		return -EINVAL;
	adv7183_write(sd, ADV7183_IN_CTRL, reg);

	decoder->std = std;

	return 0;
}