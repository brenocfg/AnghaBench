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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dss_uninit_overlay_managers () ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 

__attribute__((used)) static void dispc_unbind(struct device *dev, struct device *master,
			       void *data)
{
	pm_runtime_disable(dev);

	dss_uninit_overlay_managers();
}