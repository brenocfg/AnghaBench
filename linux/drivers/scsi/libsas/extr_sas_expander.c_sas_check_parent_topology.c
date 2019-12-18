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
struct expander_device {int num_phys; int /*<<< orphan*/  t2t_supp; struct ex_phy* ex_phy; } ;
struct ex_phy {scalar_t__ phy_state; size_t attached_phy_id; int /*<<< orphan*/  routing_attr; int /*<<< orphan*/  attached_sas_addr; } ;
struct domain_device {int dev_type; TYPE_1__* parent; int /*<<< orphan*/  sas_addr; struct expander_device ex_dev; } ;
struct TYPE_2__ {int dev_type; struct expander_device ex_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ PHY_NOT_PRESENT ; 
 scalar_t__ PHY_VACANT ; 
 scalar_t__ SAS_ADDR (int /*<<< orphan*/ ) ; 
#define  SAS_EDGE_EXPANDER_DEVICE 129 
#define  SAS_FANOUT_EXPANDER_DEVICE 128 
 int /*<<< orphan*/  SUBTRACTIVE_ROUTING ; 
 int /*<<< orphan*/  TABLE_ROUTING ; 
 int /*<<< orphan*/  dev_is_expander (int) ; 
 int sas_check_eeds (struct domain_device*,struct ex_phy*,struct ex_phy*) ; 
 int /*<<< orphan*/  sas_print_parent_topology_bug (struct domain_device*,struct ex_phy*,struct ex_phy*) ; 

__attribute__((used)) static int sas_check_parent_topology(struct domain_device *child)
{
	struct expander_device *child_ex = &child->ex_dev;
	struct expander_device *parent_ex;
	int i;
	int res = 0;

	if (!child->parent)
		return 0;

	if (!dev_is_expander(child->parent->dev_type))
		return 0;

	parent_ex = &child->parent->ex_dev;

	for (i = 0; i < parent_ex->num_phys; i++) {
		struct ex_phy *parent_phy = &parent_ex->ex_phy[i];
		struct ex_phy *child_phy;

		if (parent_phy->phy_state == PHY_VACANT ||
		    parent_phy->phy_state == PHY_NOT_PRESENT)
			continue;

		if (SAS_ADDR(parent_phy->attached_sas_addr) != SAS_ADDR(child->sas_addr))
			continue;

		child_phy = &child_ex->ex_phy[parent_phy->attached_phy_id];

		switch (child->parent->dev_type) {
		case SAS_EDGE_EXPANDER_DEVICE:
			if (child->dev_type == SAS_FANOUT_EXPANDER_DEVICE) {
				if (parent_phy->routing_attr != SUBTRACTIVE_ROUTING ||
				    child_phy->routing_attr != TABLE_ROUTING) {
					sas_print_parent_topology_bug(child, parent_phy, child_phy);
					res = -ENODEV;
				}
			} else if (parent_phy->routing_attr == SUBTRACTIVE_ROUTING) {
				if (child_phy->routing_attr == SUBTRACTIVE_ROUTING) {
					res = sas_check_eeds(child, parent_phy, child_phy);
				} else if (child_phy->routing_attr != TABLE_ROUTING) {
					sas_print_parent_topology_bug(child, parent_phy, child_phy);
					res = -ENODEV;
				}
			} else if (parent_phy->routing_attr == TABLE_ROUTING) {
				if (child_phy->routing_attr == SUBTRACTIVE_ROUTING ||
				    (child_phy->routing_attr == TABLE_ROUTING &&
				     child_ex->t2t_supp && parent_ex->t2t_supp)) {
					/* All good */;
				} else {
					sas_print_parent_topology_bug(child, parent_phy, child_phy);
					res = -ENODEV;
				}
			}
			break;
		case SAS_FANOUT_EXPANDER_DEVICE:
			if (parent_phy->routing_attr != TABLE_ROUTING ||
			    child_phy->routing_attr != SUBTRACTIVE_ROUTING) {
				sas_print_parent_topology_bug(child, parent_phy, child_phy);
				res = -ENODEV;
			}
			break;
		default:
			break;
		}
	}

	return res;
}