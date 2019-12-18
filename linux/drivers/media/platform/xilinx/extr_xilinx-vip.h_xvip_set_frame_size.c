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
struct xvip_device {int dummy; } ;
struct v4l2_mbus_framefmt {int height; int width; } ;

/* Variables and functions */
 int XVIP_ACTIVE_HSIZE_SHIFT ; 
 int /*<<< orphan*/  XVIP_ACTIVE_SIZE ; 
 int XVIP_ACTIVE_VSIZE_SHIFT ; 
 int /*<<< orphan*/  xvip_write (struct xvip_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void xvip_set_frame_size(struct xvip_device *xvip,
				       const struct v4l2_mbus_framefmt *format)
{
	xvip_write(xvip, XVIP_ACTIVE_SIZE,
		   (format->height << XVIP_ACTIVE_VSIZE_SHIFT) |
		   (format->width << XVIP_ACTIVE_HSIZE_SHIFT));
}