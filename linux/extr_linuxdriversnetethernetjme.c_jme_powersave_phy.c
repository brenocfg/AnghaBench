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
struct jme_adapter {int reg_pmcs; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PMCS_LFEN ; 
 int PMCS_LREN ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jme_clear_pm_enable_wol (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_phy_off (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_set_100m_half (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_wait_link (struct jme_adapter*) ; 

__attribute__((used)) static void
jme_powersave_phy(struct jme_adapter *jme)
{
	if (jme->reg_pmcs && device_may_wakeup(&jme->pdev->dev)) {
		jme_set_100m_half(jme);
		if (jme->reg_pmcs & (PMCS_LFEN | PMCS_LREN))
			jme_wait_link(jme);
		jme_clear_pm_enable_wol(jme);
	} else {
		jme_phy_off(jme);
	}
}