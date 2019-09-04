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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int /*<<< orphan*/  name; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int dlpar_acquire_drc (int /*<<< orphan*/ ) ; 
 int dlpar_detach_node (struct device_node*) ; 
 int dlpar_offline_cpu (struct device_node*) ; 
 int /*<<< orphan*/  dlpar_online_cpu (struct device_node*) ; 
 int dlpar_release_drc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static ssize_t dlpar_cpu_remove(struct device_node *dn, u32 drc_index)
{
	int rc;

	pr_debug("Attempting to remove CPU %s, drc index: %x\n",
		 dn->name, drc_index);

	rc = dlpar_offline_cpu(dn);
	if (rc) {
		pr_warn("Failed to offline CPU %s, rc: %d\n", dn->name, rc);
		return -EINVAL;
	}

	rc = dlpar_release_drc(drc_index);
	if (rc) {
		pr_warn("Failed to release drc (%x) for CPU %s, rc: %d\n",
			drc_index, dn->name, rc);
		dlpar_online_cpu(dn);
		return rc;
	}

	rc = dlpar_detach_node(dn);
	if (rc) {
		int saved_rc = rc;

		pr_warn("Failed to detach CPU %s, rc: %d", dn->name, rc);

		rc = dlpar_acquire_drc(drc_index);
		if (!rc)
			dlpar_online_cpu(dn);

		return saved_rc;
	}

	pr_debug("Successfully removed CPU, drc index: %x\n", drc_index);
	return 0;
}