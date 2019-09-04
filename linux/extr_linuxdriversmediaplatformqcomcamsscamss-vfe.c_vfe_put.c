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
struct vfe_device {int power_count; int /*<<< orphan*/  power_lock; int /*<<< orphan*/  id; TYPE_1__* camss; int /*<<< orphan*/  clock; int /*<<< orphan*/  nclocks; scalar_t__ was_streaming; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  camss_disable_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camss_pm_domain_off (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_halt (struct vfe_device*) ; 

__attribute__((used)) static void vfe_put(struct vfe_device *vfe)
{
	mutex_lock(&vfe->power_lock);

	if (vfe->power_count == 0) {
		dev_err(vfe->camss->dev, "vfe power off on power_count == 0\n");
		goto exit;
	} else if (vfe->power_count == 1) {
		if (vfe->was_streaming) {
			vfe->was_streaming = 0;
			vfe_halt(vfe);
		}
		camss_disable_clocks(vfe->nclocks, vfe->clock);
		pm_runtime_put_sync(vfe->camss->dev);
		camss_pm_domain_off(vfe->camss, vfe->id);
	}

	vfe->power_count--;

exit:
	mutex_unlock(&vfe->power_lock);
}