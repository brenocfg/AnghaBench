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
struct omap_overlay_manager {int /*<<< orphan*/  name; } ;
struct mgr_priv_data {scalar_t__ busy; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ) ; 
 int dss_check_settings (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  dss_mgr_write_regs (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  dss_mgr_write_regs_extra (struct omap_overlay_manager*) ; 
 struct mgr_priv_data* get_mgr_priv (struct omap_overlay_manager*) ; 
 scalar_t__ mgr_manual_update (struct omap_overlay_manager*) ; 
 int omap_dss_get_num_overlay_managers () ; 
 struct omap_overlay_manager* omap_dss_get_overlay_manager (int) ; 

__attribute__((used)) static void dss_write_regs(void)
{
	const int num_mgrs = omap_dss_get_num_overlay_managers();
	int i;

	for (i = 0; i < num_mgrs; ++i) {
		struct omap_overlay_manager *mgr;
		struct mgr_priv_data *mp;
		int r;

		mgr = omap_dss_get_overlay_manager(i);
		mp = get_mgr_priv(mgr);

		if (!mp->enabled || mgr_manual_update(mgr) || mp->busy)
			continue;

		r = dss_check_settings(mgr);
		if (r) {
			DSSERR("cannot write registers for manager %s: "
					"illegal configuration\n", mgr->name);
			continue;
		}

		dss_mgr_write_regs(mgr);
		dss_mgr_write_regs_extra(mgr);
	}
}