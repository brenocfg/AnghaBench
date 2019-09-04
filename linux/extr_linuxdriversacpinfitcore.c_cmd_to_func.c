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
struct nfit_mem {scalar_t__ family; } ;
struct nd_cmd_pkg {scalar_t__ nd_family; int nd_command; scalar_t__* nd_reserved2; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int ENOTTY ; 
 scalar_t__ NVDIMM_FAMILY_INTEL ; 

__attribute__((used)) static int cmd_to_func(struct nfit_mem *nfit_mem, unsigned int cmd,
		struct nd_cmd_pkg *call_pkg)
{
	if (call_pkg) {
		int i;

		if (nfit_mem && nfit_mem->family != call_pkg->nd_family)
			return -ENOTTY;

		for (i = 0; i < ARRAY_SIZE(call_pkg->nd_reserved2); i++)
			if (call_pkg->nd_reserved2[i])
				return -EINVAL;
		return call_pkg->nd_command;
	}

	/* In the !call_pkg case, bus commands == bus functions */
	if (!nfit_mem)
		return cmd;

	/* Linux ND commands == NVDIMM_FAMILY_INTEL function numbers */
	if (nfit_mem->family == NVDIMM_FAMILY_INTEL)
		return cmd;

	/*
	 * Force function number validation to fail since 0 is never
	 * published as a valid function in dsm_mask.
	 */
	return 0;
}