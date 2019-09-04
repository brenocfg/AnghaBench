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
 int MASK_ADV7511_MSEN_DETECT ; 
 int adv7511_rd (struct v4l2_subdev*,int) ; 

__attribute__((used)) static inline bool adv7511_have_rx_sense(struct v4l2_subdev *sd)
{
	return adv7511_rd(sd, 0x42) & MASK_ADV7511_MSEN_DETECT;
}