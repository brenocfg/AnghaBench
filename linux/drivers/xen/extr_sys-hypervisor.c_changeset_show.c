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
struct hyp_sysfs_attr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HYPERVISOR_xen_version (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XENVER_changeset ; 
 int /*<<< orphan*/  XEN_CHANGESET_INFO_LEN ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t changeset_show(struct hyp_sysfs_attr *attr, char *buffer)
{
	int ret = -ENOMEM;
	char *cset;

	cset = kmalloc(XEN_CHANGESET_INFO_LEN, GFP_KERNEL);
	if (cset) {
		ret = HYPERVISOR_xen_version(XENVER_changeset, cset);
		if (!ret)
			ret = sprintf(buffer, "%s\n", cset);
		kfree(cset);
	}

	return ret;
}