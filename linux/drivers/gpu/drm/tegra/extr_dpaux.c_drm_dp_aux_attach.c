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
struct TYPE_2__ {int /*<<< orphan*/  polled; } ;
struct tegra_output {TYPE_1__ connector; } ;
struct tegra_dpaux {int /*<<< orphan*/  irq; int /*<<< orphan*/  vdd; struct tegra_output* output; } ;
struct drm_dp_aux {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int ETIMEDOUT ; 
 int connector_status_connected ; 
 int drm_dp_aux_detect (struct drm_dp_aux*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 struct tegra_dpaux* to_dpaux (struct drm_dp_aux*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int drm_dp_aux_attach(struct drm_dp_aux *aux, struct tegra_output *output)
{
	struct tegra_dpaux *dpaux = to_dpaux(aux);
	unsigned long timeout;
	int err;

	output->connector.polled = DRM_CONNECTOR_POLL_HPD;
	dpaux->output = output;

	err = regulator_enable(dpaux->vdd);
	if (err < 0)
		return err;

	timeout = jiffies + msecs_to_jiffies(250);

	while (time_before(jiffies, timeout)) {
		enum drm_connector_status status;

		status = drm_dp_aux_detect(aux);
		if (status == connector_status_connected) {
			enable_irq(dpaux->irq);
			return 0;
		}

		usleep_range(1000, 2000);
	}

	return -ETIMEDOUT;
}