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
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 scalar_t__ uvc_clock_param ; 

__attribute__((used)) static inline ktime_t uvc_video_get_time(void)
{
	if (uvc_clock_param == CLOCK_MONOTONIC)
		return ktime_get();
	else
		return ktime_get_real();
}