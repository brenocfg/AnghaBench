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
typedef  int /*<<< orphan*/  s32 ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
#define  V4L2_FIELD_BOTTOM 129 
#define  V4L2_FIELD_TOP 128 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 get_poc(enum v4l2_field field, s32 top_field_order_cnt,
		   s32 bottom_field_order_cnt)
{
	switch (field) {
	case V4L2_FIELD_TOP:
		return top_field_order_cnt;
	case V4L2_FIELD_BOTTOM:
		return bottom_field_order_cnt;
	default:
		break;
	}

	return min(top_field_order_cnt, bottom_field_order_cnt);
}