#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  read; int /*<<< orphan*/  size; TYPE_1__ attr; } ;
struct property {int /*<<< orphan*/  name; TYPE_2__ attr; int /*<<< orphan*/  length; } ;
struct device_node {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SYSFS ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_kset ; 
 int /*<<< orphan*/  of_node_is_attached (struct device_node*) ; 
 int /*<<< orphan*/  of_node_property_read ; 
 int /*<<< orphan*/  safe_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sysfs_bin_attr_init (TYPE_2__*) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,TYPE_2__*) ; 

int __of_add_property_sysfs(struct device_node *np, struct property *pp)
{
	int rc;

	/* Important: Don't leak passwords */
	bool secure = strncmp(pp->name, "security-", 9) == 0;

	if (!IS_ENABLED(CONFIG_SYSFS))
		return 0;

	if (!of_kset || !of_node_is_attached(np))
		return 0;

	sysfs_bin_attr_init(&pp->attr);
	pp->attr.attr.name = safe_name(&np->kobj, pp->name);
	pp->attr.attr.mode = secure ? 0400 : 0444;
	pp->attr.size = secure ? 0 : pp->length;
	pp->attr.read = of_node_property_read;

	rc = sysfs_create_bin_file(&np->kobj, &pp->attr);
	WARN(rc, "error adding attribute %s to node %pOF\n", pp->name, np);
	return rc;
}