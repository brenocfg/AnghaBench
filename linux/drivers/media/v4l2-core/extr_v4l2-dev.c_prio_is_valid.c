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
typedef  enum v4l2_priority { ____Placeholder_v4l2_priority } v4l2_priority ;

/* Variables and functions */
 int V4L2_PRIORITY_BACKGROUND ; 
 int V4L2_PRIORITY_INTERACTIVE ; 
 int V4L2_PRIORITY_RECORD ; 

__attribute__((used)) static inline bool prio_is_valid(enum v4l2_priority prio)
{
	return prio == V4L2_PRIORITY_BACKGROUND ||
	       prio == V4L2_PRIORITY_INTERACTIVE ||
	       prio == V4L2_PRIORITY_RECORD;
}