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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int io_read (struct v4l2_subdev*,scalar_t__) ; 

__attribute__((used)) static unsigned int io_readn(struct v4l2_subdev *sd, u16 reg, u8 len, u8 *data)
{
	int i;
	int sz = 0;
	int val;

	for (i = 0; i < len; i++) {
		val = io_read(sd, reg + i);
		if (val < 0)
			break;
		data[i] = val;
		sz++;
	}

	return sz;
}