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
typedef  int u16 ;
struct enetc_pf {TYPE_2__* si; struct enetc_msg_swbd* rxmsg; } ;
struct enetc_msg_swbd {scalar_t__ vaddr; } ;
struct enetc_msg_cmd_header {int type; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
#define  ENETC_MSG_CMD_MNG_MAC 128 
 int ENETC_MSG_CMD_STATUS_OK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int enetc_msg_pf_set_vf_primary_mac_addr (struct enetc_pf*,int) ; 

void enetc_msg_handle_rxmsg(struct enetc_pf *pf, int vf_id, u16 *status)
{
	struct enetc_msg_swbd *msg = &pf->rxmsg[vf_id];
	struct device *dev = &pf->si->pdev->dev;
	struct enetc_msg_cmd_header *cmd_hdr;
	u16 cmd_type;

	*status = ENETC_MSG_CMD_STATUS_OK;
	cmd_hdr = (struct enetc_msg_cmd_header *)msg->vaddr;
	cmd_type = cmd_hdr->type;

	switch (cmd_type) {
	case ENETC_MSG_CMD_MNG_MAC:
		*status = enetc_msg_pf_set_vf_primary_mac_addr(pf, vf_id);
		break;
	default:
		dev_err(dev, "command not supported (cmd_type: 0x%x)\n",
			cmd_type);
	}
}