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
struct v4l2_rect {int width; int height; } ;

/* Variables and functions */

__attribute__((used)) static bool is_unscaled_ok(int width, int height, struct v4l2_rect *rect)
{
	return width > rect->width >> 1 || height > rect->height >> 1;
}