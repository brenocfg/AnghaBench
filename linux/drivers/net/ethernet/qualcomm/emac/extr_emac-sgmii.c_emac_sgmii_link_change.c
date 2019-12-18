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
struct TYPE_4__ {TYPE_1__* sgmii_ops; } ;
struct emac_adapter {TYPE_2__ phy; } ;
struct TYPE_3__ {int (* link_change ) (struct emac_adapter*,int) ;} ;

/* Variables and functions */
 int stub1 (struct emac_adapter*,int) ; 

int emac_sgmii_link_change(struct emac_adapter *adpt, bool link_state)
{
	if (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->link_change))
		return 0;

	return adpt->phy.sgmii_ops->link_change(adpt, link_state);
}