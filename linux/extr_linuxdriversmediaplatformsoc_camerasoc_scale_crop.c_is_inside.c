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
struct v4l2_rect {scalar_t__ left; scalar_t__ top; scalar_t__ width; scalar_t__ height; } ;

/* Variables and functions */

__attribute__((used)) static bool is_inside(const struct v4l2_rect *r1, const struct v4l2_rect *r2)
{
	return r1->left > r2->left || r1->top > r2->top ||
		r1->left + r1->width < r2->left + r2->width ||
		r1->top + r1->height < r2->top + r2->height;
}