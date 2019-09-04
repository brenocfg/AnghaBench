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
struct msi_domain_info {struct its_node* data; int /*<<< orphan*/ * ops; } ;
struct its_node {int /*<<< orphan*/  msi_domain_flags; } ;
struct irq_domain {struct msi_domain_info* host_data; int /*<<< orphan*/  flags; int /*<<< orphan*/  parent; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_BUS_NEXUS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct irq_domain* irq_domain_create_tree (struct fwnode_handle*,int /*<<< orphan*/ *,struct its_node*) ; 
 int /*<<< orphan*/  irq_domain_update_bus_token (struct irq_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_domain_ops ; 
 int /*<<< orphan*/  its_msi_domain_ops ; 
 int /*<<< orphan*/  its_parent ; 
 int /*<<< orphan*/  kfree (struct msi_domain_info*) ; 
 struct msi_domain_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int its_init_domain(struct fwnode_handle *handle, struct its_node *its)
{
	struct irq_domain *inner_domain;
	struct msi_domain_info *info;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	inner_domain = irq_domain_create_tree(handle, &its_domain_ops, its);
	if (!inner_domain) {
		kfree(info);
		return -ENOMEM;
	}

	inner_domain->parent = its_parent;
	irq_domain_update_bus_token(inner_domain, DOMAIN_BUS_NEXUS);
	inner_domain->flags |= its->msi_domain_flags;
	info->ops = &its_msi_domain_ops;
	info->data = its;
	inner_domain->host_data = info;

	return 0;
}