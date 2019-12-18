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
struct videobuf_queue {int field; scalar_t__ last; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int V4L2_FIELD_ALTERNATE ; 
 int V4L2_FIELD_ANY ; 
 void* V4L2_FIELD_BOTTOM ; 
 scalar_t__ V4L2_FIELD_TOP ; 

enum v4l2_field videobuf_next_field(struct videobuf_queue *q)
{
	enum v4l2_field field = q->field;

	BUG_ON(V4L2_FIELD_ANY == field);

	if (V4L2_FIELD_ALTERNATE == field) {
		if (V4L2_FIELD_TOP == q->last) {
			field   = V4L2_FIELD_BOTTOM;
			q->last = V4L2_FIELD_BOTTOM;
		} else {
			field   = V4L2_FIELD_TOP;
			q->last = V4L2_FIELD_TOP;
		}
	}
	return field;
}