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
 int /*<<< orphan*/  adv7511_wr (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  adv7511_wr_and_or (struct v4l2_subdev*,int,int,int) ; 

__attribute__((used)) static int adv7511_s_routing(struct v4l2_subdev *sd, u32 input, u32 output, u32 config)
{
	/* Only 2 channels in use for application */
	adv7511_wr_and_or(sd, 0x73, 0xf8, 0x1);
	/* Speaker mapping */
	adv7511_wr(sd, 0x76, 0x00);

	/* 16 bit audio word length */
	adv7511_wr_and_or(sd, 0x14, 0xf0, 0x02);

	return 0;
}