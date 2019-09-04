#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfe_device {scalar_t__ power_count; int /*<<< orphan*/  power_lock; int /*<<< orphan*/  id; TYPE_1__* camss; int /*<<< orphan*/  clock; int /*<<< orphan*/  nclocks; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  camss_disable_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int camss_enable_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camss_pm_domain_off (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int camss_pm_domain_on (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int vfe_check_clock_rates (struct vfe_device*) ; 
 int /*<<< orphan*/  vfe_init_outputs (struct vfe_device*) ; 
 int vfe_reset (struct vfe_device*) ; 
 int /*<<< orphan*/  vfe_reset_output_maps (struct vfe_device*) ; 
 int vfe_set_clock_rates (struct vfe_device*) ; 

__attribute__((used)) static int vfe_get(struct vfe_device *vfe)
{
	int ret;

	mutex_lock(&vfe->power_lock);

	if (vfe->power_count == 0) {
		ret = camss_pm_domain_on(vfe->camss, vfe->id);
		if (ret < 0)
			goto error_pm_domain;

		ret = pm_runtime_get_sync(vfe->camss->dev);
		if (ret < 0)
			goto error_pm_runtime_get;

		ret = vfe_set_clock_rates(vfe);
		if (ret < 0)
			goto error_clocks;

		ret = camss_enable_clocks(vfe->nclocks, vfe->clock,
					  vfe->camss->dev);
		if (ret < 0)
			goto error_clocks;

		ret = vfe_reset(vfe);
		if (ret < 0)
			goto error_reset;

		vfe_reset_output_maps(vfe);

		vfe_init_outputs(vfe);
	} else {
		ret = vfe_check_clock_rates(vfe);
		if (ret < 0)
			goto error_clocks;
	}
	vfe->power_count++;

	mutex_unlock(&vfe->power_lock);

	return 0;

error_reset:
	camss_disable_clocks(vfe->nclocks, vfe->clock);

error_clocks:
	pm_runtime_put_sync(vfe->camss->dev);

error_pm_runtime_get:
	camss_pm_domain_off(vfe->camss, vfe->id);

error_pm_domain:
	mutex_unlock(&vfe->power_lock);

	return ret;
}