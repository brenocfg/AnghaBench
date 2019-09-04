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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  initialized ; 
 scalar_t__ off ; 

bool cpuidle_not_available(struct cpuidle_driver *drv,
			   struct cpuidle_device *dev)
{
	return off || !initialized || !drv || !dev || !dev->enabled;
}