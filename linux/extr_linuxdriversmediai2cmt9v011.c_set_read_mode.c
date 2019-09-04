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
struct mt9v011 {scalar_t__ vflip; scalar_t__ hflip; } ;

/* Variables and functions */
 int /*<<< orphan*/  R20_MT9V011_READ_MODE ; 
 int /*<<< orphan*/  mt9v011_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned int) ; 
 struct mt9v011* to_mt9v011 (struct v4l2_subdev*) ; 

__attribute__((used)) static void set_read_mode(struct v4l2_subdev *sd)
{
	struct mt9v011 *core = to_mt9v011(sd);
	unsigned mode = 0x1000;

	if (core->hflip)
		mode |= 0x4000;

	if (core->vflip)
		mode |= 0x8000;

	mt9v011_write(sd, R20_MT9V011_READ_MODE, mode);
}