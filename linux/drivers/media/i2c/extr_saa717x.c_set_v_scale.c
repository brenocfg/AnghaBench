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
 int /*<<< orphan*/  saa717x_write (struct v4l2_subdev*,int,int) ; 

__attribute__((used)) static void set_v_scale(struct v4l2_subdev *sd, int task, int yscale)
{
	int task_shift;

	task_shift = task * 0x40;
	/* Vertical scaling ratio (LOW) */
	saa717x_write(sd, 0x70 + task_shift, yscale & 0xff);
	/* Vertical scaling ratio (HI) */
	saa717x_write(sd, 0x71 + task_shift, yscale >> 8);
}