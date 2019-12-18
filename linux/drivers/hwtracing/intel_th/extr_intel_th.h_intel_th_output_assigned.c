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
struct TYPE_2__ {scalar_t__ port; scalar_t__ type; } ;
struct intel_th_device {scalar_t__ type; TYPE_1__ output; } ;

/* Variables and functions */
 scalar_t__ GTH_NONE ; 
 scalar_t__ INTEL_TH_OUTPUT ; 

__attribute__((used)) static inline bool
intel_th_output_assigned(struct intel_th_device *thdev)
{
	return thdev->type == INTEL_TH_OUTPUT &&
		(thdev->output.port >= 0 ||
		 thdev->output.type == GTH_NONE);
}