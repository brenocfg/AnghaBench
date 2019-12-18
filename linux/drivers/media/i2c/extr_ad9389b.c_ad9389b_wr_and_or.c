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
 int ad9389b_rd (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  ad9389b_wr (struct v4l2_subdev*,int,int) ; 

__attribute__((used)) static inline void ad9389b_wr_and_or(struct v4l2_subdev *sd, u8 reg,
				     u8 clr_mask, u8 val_mask)
{
	ad9389b_wr(sd, reg, (ad9389b_rd(sd, reg) & clr_mask) | val_mask);
}