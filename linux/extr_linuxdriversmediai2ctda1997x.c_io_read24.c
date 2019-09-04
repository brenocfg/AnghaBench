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
typedef  scalar_t__ u16 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int io_read (struct v4l2_subdev*,scalar_t__) ; 

__attribute__((used)) static inline long io_read24(struct v4l2_subdev *sd, u16 reg)
{
	int val;
	long lval = 0;

	val = io_read(sd, reg);
	if (val < 0)
		return val;
	lval |= (val << 16);
	val = io_read(sd, reg + 1);
	if (val < 0)
		return val;
	lval |= (val << 8);
	val = io_read(sd, reg + 2);
	if (val < 0)
		return val;
	lval |= val;

	return lval;
}