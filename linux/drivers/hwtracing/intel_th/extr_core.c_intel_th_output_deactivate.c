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
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct intel_th_driver {TYPE_1__ driver; int /*<<< orphan*/  (* deactivate ) (struct intel_th_device*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  driver; } ;
struct intel_th_device {TYPE_2__ dev; } ;
struct intel_th {int /*<<< orphan*/  (* deactivate ) (struct intel_th*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  intel_th_trace_disable (struct intel_th_device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct intel_th_device*) ; 
 int /*<<< orphan*/  stub2 (struct intel_th*) ; 
 struct intel_th* to_intel_th (struct intel_th_device*) ; 
 struct intel_th_driver* to_intel_th_driver_or_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_th_output_deactivate(struct intel_th_device *thdev)
{
	struct intel_th_driver *thdrv =
		to_intel_th_driver_or_null(thdev->dev.driver);
	struct intel_th *th = to_intel_th(thdev);

	if (!thdrv)
		return;

	if (thdrv->deactivate)
		thdrv->deactivate(thdev);
	else
		intel_th_trace_disable(thdev);

	if (th->deactivate)
		th->deactivate(th);

	pm_runtime_put(&thdev->dev);
	module_put(thdrv->driver.owner);
}