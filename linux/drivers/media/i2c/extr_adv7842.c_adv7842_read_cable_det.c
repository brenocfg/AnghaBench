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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int io_read (struct v4l2_subdev*,int) ; 

__attribute__((used)) static u16 adv7842_read_cable_det(struct v4l2_subdev *sd)
{
	u8 reg = io_read(sd, 0x6f);
	u16 val = 0;

	if (reg & 0x02)
		val |= 1; /* port A */
	if (reg & 0x01)
		val |= 2; /* port B */
	return val;
}