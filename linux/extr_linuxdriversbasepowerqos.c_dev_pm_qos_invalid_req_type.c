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
struct TYPE_2__ {int /*<<< orphan*/  set_latency_tolerance; } ;
struct device {TYPE_1__ power; } ;
typedef  enum dev_pm_qos_req_type { ____Placeholder_dev_pm_qos_req_type } dev_pm_qos_req_type ;

/* Variables and functions */
 int DEV_PM_QOS_LATENCY_TOLERANCE ; 

__attribute__((used)) static bool dev_pm_qos_invalid_req_type(struct device *dev,
					enum dev_pm_qos_req_type type)
{
	return type == DEV_PM_QOS_LATENCY_TOLERANCE &&
	       !dev->power.set_latency_tolerance;
}