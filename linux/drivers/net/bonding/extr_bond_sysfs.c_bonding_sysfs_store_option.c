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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
struct bonding {int dummy; } ;
struct bond_option {int /*<<< orphan*/  id; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 struct bond_option* bond_opt_get_by_name (int /*<<< orphan*/ ) ; 
 int bond_opt_tryset_rtnl (struct bonding*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,size_t,int /*<<< orphan*/ ) ; 
 struct bonding* to_bond (struct device*) ; 

__attribute__((used)) static ssize_t bonding_sysfs_store_option(struct device *d,
					  struct device_attribute *attr,
					  const char *buffer, size_t count)
{
	struct bonding *bond = to_bond(d);
	const struct bond_option *opt;
	char *buffer_clone;
	int ret;

	opt = bond_opt_get_by_name(attr->attr.name);
	if (WARN_ON(!opt))
		return -ENOENT;
	buffer_clone = kstrndup(buffer, count, GFP_KERNEL);
	if (!buffer_clone)
		return -ENOMEM;
	ret = bond_opt_tryset_rtnl(bond, opt->id, buffer_clone);
	if (!ret)
		ret = count;
	kfree(buffer_clone);

	return ret;
}