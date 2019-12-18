#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct enetc_vf_state {int flags; } ;
struct enetc_pf {TYPE_4__* si; struct enetc_msg_swbd* rxmsg; struct enetc_vf_state* vf_state; } ;
struct enetc_msg_swbd {scalar_t__ vaddr; } ;
struct TYPE_7__ {char* sa_data; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct enetc_msg_cmd_set_primary_mac {TYPE_3__ mac; TYPE_2__ header; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  hw; TYPE_1__* pdev; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ ENETC_MSG_CMD_MNG_ADD ; 
 scalar_t__ ENETC_MSG_CMD_STATUS_FAIL ; 
 scalar_t__ ENETC_MSG_CMD_STATUS_OK ; 
 int ENETC_VF_FLAG_PF_SET_MAC ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  enetc_pf_set_primary_mac_addr (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static u16 enetc_msg_pf_set_vf_primary_mac_addr(struct enetc_pf *pf,
						int vf_id)
{
	struct enetc_vf_state *vf_state = &pf->vf_state[vf_id];
	struct enetc_msg_swbd *msg = &pf->rxmsg[vf_id];
	struct enetc_msg_cmd_set_primary_mac *cmd;
	struct device *dev = &pf->si->pdev->dev;
	u16 cmd_id;
	char *addr;

	cmd = (struct enetc_msg_cmd_set_primary_mac *)msg->vaddr;
	cmd_id = cmd->header.id;
	if (cmd_id != ENETC_MSG_CMD_MNG_ADD)
		return ENETC_MSG_CMD_STATUS_FAIL;

	addr = cmd->mac.sa_data;
	if (vf_state->flags & ENETC_VF_FLAG_PF_SET_MAC)
		dev_warn(dev, "Attempt to override PF set mac addr for VF%d\n",
			 vf_id);
	else
		enetc_pf_set_primary_mac_addr(&pf->si->hw, vf_id + 1, addr);

	return ENETC_MSG_CMD_STATUS_OK;
}