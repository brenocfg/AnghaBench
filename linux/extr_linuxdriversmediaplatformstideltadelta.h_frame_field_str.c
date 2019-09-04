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
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int V4L2_FIELD_BOTTOM ; 
 int V4L2_FIELD_INTERLACED ; 
 int V4L2_FIELD_INTERLACED_BT ; 
 int V4L2_FIELD_INTERLACED_TB ; 
 int V4L2_FIELD_NONE ; 
 int V4L2_FIELD_TOP ; 

__attribute__((used)) static inline char *frame_field_str(enum v4l2_field field)
{
	if (field == V4L2_FIELD_NONE)
		return "-";
	if (field == V4L2_FIELD_TOP)
		return "T";
	if (field == V4L2_FIELD_BOTTOM)
		return "B";
	if (field == V4L2_FIELD_INTERLACED)
		return "I";
	if (field == V4L2_FIELD_INTERLACED_TB)
		return "TB";
	if (field == V4L2_FIELD_INTERLACED_BT)
		return "BT";
	return "?";
}