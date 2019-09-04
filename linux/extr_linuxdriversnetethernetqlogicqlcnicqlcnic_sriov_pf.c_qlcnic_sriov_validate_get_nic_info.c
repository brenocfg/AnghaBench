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
struct qlcnic_vf_info {int pci_func; TYPE_2__* vp; } ;
struct TYPE_3__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct TYPE_4__ {int handle; } ;

/* Variables and functions */
 int BIT_31 ; 
 int EINVAL ; 

__attribute__((used)) static int qlcnic_sriov_validate_get_nic_info(struct qlcnic_vf_info *vf,
					      struct qlcnic_cmd_args *cmd)
{
	if (cmd->req.arg[1] & BIT_31) {
		if (((cmd->req.arg[1] >> 16) & 0x7fff) != vf->pci_func)
			return -EINVAL;
	} else {
		cmd->req.arg[1] |= vf->vp->handle << 16;
	}

	return 0;
}