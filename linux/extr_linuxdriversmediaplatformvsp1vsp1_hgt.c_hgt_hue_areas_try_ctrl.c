#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__* p_u8; } ;
struct v4l2_ctrl {TYPE_1__ p_new; } ;

/* Variables and functions */
 int EINVAL ; 
 int HGT_NUM_HUE_AREAS ; 

__attribute__((used)) static int hgt_hue_areas_try_ctrl(struct v4l2_ctrl *ctrl)
{
	const u8 *values = ctrl->p_new.p_u8;
	unsigned int i;

	/*
	 * The hardware has constraints on the hue area boundaries beyond the
	 * control min, max and step. The values must match one of the following
	 * expressions.
	 *
	 * 0L <= 0U <= 1L <= 1U <= 2L <= 2U <= 3L <= 3U <= 4L <= 4U <= 5L <= 5U
	 * 0U <= 1L <= 1U <= 2L <= 2U <= 3L <= 3U <= 4L <= 4U <= 5L <= 5U <= 0L
	 *
	 * Start by verifying the common part...
	 */
	for (i = 1; i < (HGT_NUM_HUE_AREAS * 2) - 1; ++i) {
		if (values[i] > values[i+1])
			return -EINVAL;
	}

	/* ... and handle 0L separately. */
	if (values[0] > values[1] && values[11] > values[0])
		return -EINVAL;

	return 0;
}