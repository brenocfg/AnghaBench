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
struct intel_th_device {scalar_t__ type; } ;
struct TYPE_2__ {struct intel_th_device* hub; } ;

/* Variables and functions */
 scalar_t__ INTEL_TH_OUTPUT ; 
 scalar_t__ INTEL_TH_SWITCH ; 
 TYPE_1__* to_intel_th (struct intel_th_device*) ; 
 struct intel_th_device* to_intel_th_parent (struct intel_th_device*) ; 

__attribute__((used)) static inline struct intel_th_device *
to_intel_th_hub(struct intel_th_device *thdev)
{
	if (thdev->type == INTEL_TH_SWITCH)
		return thdev;
	else if (thdev->type == INTEL_TH_OUTPUT)
		return to_intel_th_parent(thdev);

	return to_intel_th(thdev)->hub;
}