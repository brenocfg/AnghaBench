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
struct ex_phy {int /*<<< orphan*/  phy_id; } ;
struct domain_device {size_t dev_type; int /*<<< orphan*/  sas_addr; struct domain_device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
#define  SAS_EDGE_EXPANDER_DEVICE 129 
#define  SAS_FANOUT_EXPANDER_DEVICE 128 
 int /*<<< orphan*/  pr_notice (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_route_char (struct domain_device*,struct ex_phy*) ; 

__attribute__((used)) static void sas_print_parent_topology_bug(struct domain_device *child,
						 struct ex_phy *parent_phy,
						 struct ex_phy *child_phy)
{
	static const char *ex_type[] = {
		[SAS_EDGE_EXPANDER_DEVICE] = "edge",
		[SAS_FANOUT_EXPANDER_DEVICE] = "fanout",
	};
	struct domain_device *parent = child->parent;

	pr_notice("%s ex %016llx phy%02d <--> %s ex %016llx phy%02d has %c:%c routing link!\n",
		  ex_type[parent->dev_type],
		  SAS_ADDR(parent->sas_addr),
		  parent_phy->phy_id,

		  ex_type[child->dev_type],
		  SAS_ADDR(child->sas_addr),
		  child_phy->phy_id,

		  sas_route_char(parent, parent_phy),
		  sas_route_char(child, child_phy));
}