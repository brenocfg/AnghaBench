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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int io_read (struct v4l2_subdev*,int) ; 

__attribute__((used)) static unsigned int adv7612_read_cable_det(struct v4l2_subdev *sd)
{
	/*  Reads CABLE_DET_A_RAW. For input B support, need to
	 *  account for bit 7 [MSB] of 0x6a (ie. CABLE_DET_B_RAW)
	 */
	u8 value = io_read(sd, 0x6f);

	return value & 1;
}