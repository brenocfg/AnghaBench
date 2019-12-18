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
struct enic {int num_vfs; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int PORT_SELF_VF ; 
 int /*<<< orphan*/  enic_is_dynamic (struct enic*) ; 
 scalar_t__ enic_sriov_enabled (struct enic*) ; 

int enic_is_valid_pp_vf(struct enic *enic, int vf, int *err)
{
	if (vf != PORT_SELF_VF) {
#ifdef CONFIG_PCI_IOV
		if (enic_sriov_enabled(enic)) {
			if (vf < 0 || vf >= enic->num_vfs) {
				*err = -EINVAL;
				goto err_out;
			}
		} else {
			*err = -EOPNOTSUPP;
			goto err_out;
		}
#else
		*err = -EOPNOTSUPP;
		goto err_out;
#endif
	}

	if (vf == PORT_SELF_VF && !enic_is_dynamic(enic)) {
		*err = -EOPNOTSUPP;
		goto err_out;
	}

	*err = 0;
	return 1;

err_out:
	return 0;
}