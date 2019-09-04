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

__attribute__((used)) static int is_rectangle_enclosed(struct v4l2_rect *a, struct v4l2_rect *b)
{
	if (a->left < b->left || a->top < b->top)
		return 0;

	if (a->left + a->width > b->left + b->width)
		return 0;

	if (a->top + a->height > b->top + b->height)
		return 0;

	return 1;
}