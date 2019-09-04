#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct em28xx_v4l2 {unsigned int sensor_xres; } ;
struct TYPE_2__ {scalar_t__ max_range_640_480; } ;
struct em28xx {TYPE_1__ board; scalar_t__ is_webcam; struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int norm_maxw(struct em28xx *dev)
{
	struct em28xx_v4l2 *v4l2 = dev->v4l2;

	if (dev->is_webcam)
		return v4l2->sensor_xres;

	if (dev->board.max_range_640_480)
		return 640;

	return 720;
}