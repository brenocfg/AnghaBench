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
 int vpx3220_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpx3220_write_block(struct v4l2_subdev *sd, const u8 *data, unsigned int len)
{
	u8 reg;
	int ret = -1;

	while (len >= 2) {
		reg = *data++;
		ret = vpx3220_write(sd, reg, *data++);
		if (ret < 0)
			break;
		len -= 2;
	}

	return ret;
}