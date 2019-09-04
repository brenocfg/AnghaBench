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
struct tg3 {TYPE_1__* pdev; } ;
struct subsys_tbl_ent {scalar_t__ subsys_vendor; scalar_t__ subsys_devid; } ;
struct TYPE_2__ {scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct subsys_tbl_ent*) ; 
 struct subsys_tbl_ent* subsys_id_to_phy_id ; 

__attribute__((used)) static struct subsys_tbl_ent *tg3_lookup_by_subsys(struct tg3 *tp)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(subsys_id_to_phy_id); i++) {
		if ((subsys_id_to_phy_id[i].subsys_vendor ==
		     tp->pdev->subsystem_vendor) &&
		    (subsys_id_to_phy_id[i].subsys_devid ==
		     tp->pdev->subsystem_device))
			return &subsys_id_to_phy_id[i];
	}
	return NULL;
}