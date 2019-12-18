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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  adv7511_wr (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  adv7511_wr_and_or (struct v4l2_subdev*,int,int,int) ; 

__attribute__((used)) static void adv7511_csc_coeff(struct v4l2_subdev *sd,
			      u16 A1, u16 A2, u16 A3, u16 A4,
			      u16 B1, u16 B2, u16 B3, u16 B4,
			      u16 C1, u16 C2, u16 C3, u16 C4)
{
	/* A */
	adv7511_wr_and_or(sd, 0x18, 0xe0, A1>>8);
	adv7511_wr(sd, 0x19, A1);
	adv7511_wr_and_or(sd, 0x1A, 0xe0, A2>>8);
	adv7511_wr(sd, 0x1B, A2);
	adv7511_wr_and_or(sd, 0x1c, 0xe0, A3>>8);
	adv7511_wr(sd, 0x1d, A3);
	adv7511_wr_and_or(sd, 0x1e, 0xe0, A4>>8);
	adv7511_wr(sd, 0x1f, A4);

	/* B */
	adv7511_wr_and_or(sd, 0x20, 0xe0, B1>>8);
	adv7511_wr(sd, 0x21, B1);
	adv7511_wr_and_or(sd, 0x22, 0xe0, B2>>8);
	adv7511_wr(sd, 0x23, B2);
	adv7511_wr_and_or(sd, 0x24, 0xe0, B3>>8);
	adv7511_wr(sd, 0x25, B3);
	adv7511_wr_and_or(sd, 0x26, 0xe0, B4>>8);
	adv7511_wr(sd, 0x27, B4);

	/* C */
	adv7511_wr_and_or(sd, 0x28, 0xe0, C1>>8);
	adv7511_wr(sd, 0x29, C1);
	adv7511_wr_and_or(sd, 0x2A, 0xe0, C2>>8);
	adv7511_wr(sd, 0x2B, C2);
	adv7511_wr_and_or(sd, 0x2C, 0xe0, C3>>8);
	adv7511_wr(sd, 0x2D, C3);
	adv7511_wr_and_or(sd, 0x2E, 0xe0, C4>>8);
	adv7511_wr(sd, 0x2F, C4);
}