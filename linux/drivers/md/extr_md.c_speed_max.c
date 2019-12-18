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
struct mddev {int sync_speed_max; } ;

/* Variables and functions */
 int sysctl_speed_limit_max ; 

__attribute__((used)) static inline int speed_max(struct mddev *mddev)
{
	return mddev->sync_speed_max ?
		mddev->sync_speed_max : sysctl_speed_limit_max;
}