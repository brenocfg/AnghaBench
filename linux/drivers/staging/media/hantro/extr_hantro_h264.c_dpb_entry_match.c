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
struct v4l2_h264_dpb_entry {scalar_t__ top_field_order_cnt; scalar_t__ bottom_field_order_cnt; } ;

/* Variables and functions */

__attribute__((used)) static bool dpb_entry_match(const struct v4l2_h264_dpb_entry *a,
			    const struct v4l2_h264_dpb_entry *b)
{
	return a->top_field_order_cnt == b->top_field_order_cnt &&
	       a->bottom_field_order_cnt == b->bottom_field_order_cnt;
}