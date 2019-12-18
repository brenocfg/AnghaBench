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
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  enum selection_rect { ____Placeholder_selection_rect } selection_rect ;

/* Variables and functions */
 int R_INVALID ; 
 int /*<<< orphan*/  s5k5baf_bound_rect (struct v4l2_rect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5k5baf_set_rect_and_adjust(struct v4l2_rect **rects,
					enum selection_rect first,
					struct v4l2_rect *v)
{
	struct v4l2_rect *r, *br;
	enum selection_rect i = first;

	*rects[first] = *v;
	do {
		r = rects[i];
		br = rects[i - 1];
		s5k5baf_bound_rect(r, br->width, br->height);
	} while (++i != R_INVALID);
	*v = *rects[first];
}