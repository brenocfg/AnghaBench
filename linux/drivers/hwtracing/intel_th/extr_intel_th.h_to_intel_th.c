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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct intel_th_device {scalar_t__ type; TYPE_1__ dev; } ;
struct intel_th {int dummy; } ;

/* Variables and functions */
 scalar_t__ INTEL_TH_OUTPUT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct intel_th* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct intel_th_device* to_intel_th_parent (struct intel_th_device*) ; 

__attribute__((used)) static inline struct intel_th *to_intel_th(struct intel_th_device *thdev)
{
	if (thdev->type == INTEL_TH_OUTPUT)
		thdev = to_intel_th_parent(thdev);

	if (WARN_ON_ONCE(!thdev || thdev->type == INTEL_TH_OUTPUT))
		return NULL;

	return dev_get_drvdata(thdev->dev.parent);
}