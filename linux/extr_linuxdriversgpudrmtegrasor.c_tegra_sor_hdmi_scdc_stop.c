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
struct tegra_sor {int /*<<< orphan*/  scdc; scalar_t__ scdc_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_sor_hdmi_scdc_disable (struct tegra_sor*) ; 

__attribute__((used)) static void tegra_sor_hdmi_scdc_stop(struct tegra_sor *sor)
{
	if (sor->scdc_enabled) {
		cancel_delayed_work_sync(&sor->scdc);
		tegra_sor_hdmi_scdc_disable(sor);
	}
}