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
struct intel_th_driver {int (* set_output ) (struct intel_th_device*,unsigned int) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct intel_th_device {scalar_t__ host_mode; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct intel_th_device*,unsigned int) ; 
 struct intel_th_driver* to_intel_th_driver (int /*<<< orphan*/ ) ; 
 struct intel_th_device* to_intel_th_hub (struct intel_th_device*) ; 

int intel_th_set_output(struct intel_th_device *thdev,
			unsigned int master)
{
	struct intel_th_device *hub = to_intel_th_hub(thdev);
	struct intel_th_driver *hubdrv = to_intel_th_driver(hub->dev.driver);

	/* In host mode, this is up to the external debugger, do nothing. */
	if (hub->host_mode)
		return 0;

	if (!hubdrv->set_output)
		return -ENOTSUPP;

	return hubdrv->set_output(hub, master);
}