#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct qlcnic_vf_info {TYPE_2__* vp; } ;
struct TYPE_6__ {int* arg; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_3__ rsp; TYPE_1__ req; } ;
struct qlcnic_bc_trans {struct qlcnic_vf_info* vf; } ;
struct TYPE_5__ {int* mac; } ;

/* Variables and functions */
#define  QLCNIC_GET_CURRENT_MAC 130 
#define  QLCNIC_SET_FAC_DEF_MAC 129 
#define  QLCNIC_SET_STATION_MAC 128 

__attribute__((used)) static int qlcnic_sriov_pf_mac_address_cmd(struct qlcnic_bc_trans *trans,
					   struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_vf_info *vf = trans->vf;
	u8 type, *mac;

	type = cmd->req.arg[1];
	switch (type) {
	case QLCNIC_SET_STATION_MAC:
	case QLCNIC_SET_FAC_DEF_MAC:
		cmd->rsp.arg[0] = (2 << 25);
		break;
	case QLCNIC_GET_CURRENT_MAC:
		cmd->rsp.arg[0] = (1 << 25);
		mac = vf->vp->mac;
		cmd->rsp.arg[2] = mac[1] | ((mac[0] << 8) & 0xff00);
		cmd->rsp.arg[1] = mac[5] | ((mac[4] << 8) & 0xff00) |
				  ((mac[3]) << 16 & 0xff0000) |
				  ((mac[2]) << 24 & 0xff000000);
	}

	return 0;
}