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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  top; int /*<<< orphan*/  width; int /*<<< orphan*/  left; } ;

/* Variables and functions */
 int /*<<< orphan*/  s5k5baf_bound_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5k5baf_bound_rect(struct v4l2_rect *r, u32 width, u32 height)
{
	s5k5baf_bound_range(&r->left, &r->width, width);
	s5k5baf_bound_range(&r->top, &r->height, height);
}