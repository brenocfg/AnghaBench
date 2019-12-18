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
struct work_struct {int dummy; } ;
struct tegra_dpaux {TYPE_2__* output; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ connector; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_helper_hpd_irq_event (int /*<<< orphan*/ ) ; 
 struct tegra_dpaux* work_to_dpaux (struct work_struct*) ; 

__attribute__((used)) static void tegra_dpaux_hotplug(struct work_struct *work)
{
	struct tegra_dpaux *dpaux = work_to_dpaux(work);

	if (dpaux->output)
		drm_helper_hpd_irq_event(dpaux->output->connector.dev);
}