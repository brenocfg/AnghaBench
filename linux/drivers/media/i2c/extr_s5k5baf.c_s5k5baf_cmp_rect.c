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
struct v4l2_rect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (struct v4l2_rect const*,struct v4l2_rect const*,int) ; 

__attribute__((used)) static bool s5k5baf_cmp_rect(const struct v4l2_rect *r1,
			     const struct v4l2_rect *r2)
{
	return !memcmp(r1, r2, sizeof(*r1));
}