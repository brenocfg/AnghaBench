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
struct fault_attr {int dummy; } ;
struct nvme_fault_inject {int dont_retry; int /*<<< orphan*/  status; struct dentry* parent; struct fault_attr attr; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  NVME_SC_INVALID_OPCODE ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,struct dentry*,int*) ; 
 struct dentry* debugfs_create_dir (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x16 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 struct fault_attr fail_default_attr ; 
 scalar_t__ fail_request ; 
 struct dentry* fault_create_debugfs_attr (char*,struct dentry*,struct fault_attr*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 int /*<<< orphan*/  setup_fault_attr (struct fault_attr*,scalar_t__) ; 

void nvme_fault_inject_init(struct nvme_fault_inject *fault_inj,
			    const char *dev_name)
{
	struct dentry *dir, *parent;
	struct fault_attr *attr = &fault_inj->attr;

	/* set default fault injection attribute */
	if (fail_request)
		setup_fault_attr(&fail_default_attr, fail_request);

	/* create debugfs directory and attribute */
	parent = debugfs_create_dir(dev_name, NULL);
	if (!parent) {
		pr_warn("%s: failed to create debugfs directory\n", dev_name);
		return;
	}

	*attr = fail_default_attr;
	dir = fault_create_debugfs_attr("fault_inject", parent, attr);
	if (IS_ERR(dir)) {
		pr_warn("%s: failed to create debugfs attr\n", dev_name);
		debugfs_remove_recursive(parent);
		return;
	}
	fault_inj->parent = parent;

	/* create debugfs for status code and dont_retry */
	fault_inj->status = NVME_SC_INVALID_OPCODE;
	fault_inj->dont_retry = true;
	debugfs_create_x16("status", 0600, dir,	&fault_inj->status);
	debugfs_create_bool("dont_retry", 0600, dir, &fault_inj->dont_retry);
}