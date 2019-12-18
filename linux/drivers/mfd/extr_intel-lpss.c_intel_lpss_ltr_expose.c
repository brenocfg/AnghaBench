#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_lpss {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  set_latency_tolerance; } ;
struct TYPE_4__ {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_pm_qos_expose_latency_tolerance (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_lpss_ltr_set ; 

__attribute__((used)) static void intel_lpss_ltr_expose(struct intel_lpss *lpss)
{
	lpss->dev->power.set_latency_tolerance = intel_lpss_ltr_set;
	dev_pm_qos_expose_latency_tolerance(lpss->dev);
}