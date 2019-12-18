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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7183_POW_MANAGE ; 
 int adv7183_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv7183_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int adv7183_reset(struct v4l2_subdev *sd, u32 val)
{
	int reg;

	reg = adv7183_read(sd, ADV7183_POW_MANAGE) | 0x80;
	adv7183_write(sd, ADV7183_POW_MANAGE, reg);
	/* wait 5ms before any further i2c writes are performed */
	usleep_range(5000, 10000);
	return 0;
}