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
struct intel_gvt_mpt {scalar_t__ type; } ;
struct TYPE_4__ {scalar_t__ hypervisor_type; int /*<<< orphan*/  dev; struct intel_gvt_mpt* mpt; int /*<<< orphan*/  initialized; } ;
struct TYPE_3__ {scalar_t__ gvt; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ INTEL_GVT_HYPERVISOR_KVM ; 
 scalar_t__ INTEL_GVT_HYPERVISOR_XEN ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_err (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ intel_gvt_host ; 
 int intel_gvt_hypervisor_host_init (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gvt_ops ; 
 TYPE_1__* kdev_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * supported_hypervisors ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int
intel_gvt_register_hypervisor(struct intel_gvt_mpt *m)
{
	int ret;
	void *gvt;

	if (!intel_gvt_host.initialized)
		return -ENODEV;

	if (m->type != INTEL_GVT_HYPERVISOR_KVM &&
	    m->type != INTEL_GVT_HYPERVISOR_XEN)
		return -EINVAL;

	/* Get a reference for device model module */
	if (!try_module_get(THIS_MODULE))
		return -ENODEV;

	intel_gvt_host.mpt = m;
	intel_gvt_host.hypervisor_type = m->type;
	gvt = (void *)kdev_to_i915(intel_gvt_host.dev)->gvt;

	ret = intel_gvt_hypervisor_host_init(intel_gvt_host.dev, gvt,
					     &intel_gvt_ops);
	if (ret < 0) {
		gvt_err("Failed to init %s hypervisor module\n",
			supported_hypervisors[intel_gvt_host.hypervisor_type]);
		module_put(THIS_MODULE);
		return -ENODEV;
	}
	gvt_dbg_core("Running with hypervisor %s in host mode\n",
		     supported_hypervisors[intel_gvt_host.hypervisor_type]);
	return 0;
}