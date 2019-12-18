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
struct ex_phy {int /*<<< orphan*/  phy_id; } ;
struct domain_device {int /*<<< orphan*/  sas_addr; TYPE_2__* port; struct domain_device* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  eeds_b; int /*<<< orphan*/  eeds_a; int /*<<< orphan*/  fanout_sas_addr; } ;
struct TYPE_4__ {TYPE_1__ disc; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ SAS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int sas_check_eeds(struct domain_device *child,
				 struct ex_phy *parent_phy,
				 struct ex_phy *child_phy)
{
	int res = 0;
	struct domain_device *parent = child->parent;

	if (SAS_ADDR(parent->port->disc.fanout_sas_addr) != 0) {
		res = -ENODEV;
		pr_warn("edge ex %016llx phy S:%02d <--> edge ex %016llx phy S:%02d, while there is a fanout ex %016llx\n",
			SAS_ADDR(parent->sas_addr),
			parent_phy->phy_id,
			SAS_ADDR(child->sas_addr),
			child_phy->phy_id,
			SAS_ADDR(parent->port->disc.fanout_sas_addr));
	} else if (SAS_ADDR(parent->port->disc.eeds_a) == 0) {
		memcpy(parent->port->disc.eeds_a, parent->sas_addr,
		       SAS_ADDR_SIZE);
		memcpy(parent->port->disc.eeds_b, child->sas_addr,
		       SAS_ADDR_SIZE);
	} else if (((SAS_ADDR(parent->port->disc.eeds_a) ==
		    SAS_ADDR(parent->sas_addr)) ||
		   (SAS_ADDR(parent->port->disc.eeds_a) ==
		    SAS_ADDR(child->sas_addr)))
		   &&
		   ((SAS_ADDR(parent->port->disc.eeds_b) ==
		     SAS_ADDR(parent->sas_addr)) ||
		    (SAS_ADDR(parent->port->disc.eeds_b) ==
		     SAS_ADDR(child->sas_addr))))
		;
	else {
		res = -ENODEV;
		pr_warn("edge ex %016llx phy%02d <--> edge ex %016llx phy%02d link forms a third EEDS!\n",
			SAS_ADDR(parent->sas_addr),
			parent_phy->phy_id,
			SAS_ADDR(child->sas_addr),
			child_phy->phy_id);
	}

	return res;
}