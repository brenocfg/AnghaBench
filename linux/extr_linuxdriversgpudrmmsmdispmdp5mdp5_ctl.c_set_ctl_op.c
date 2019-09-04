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
typedef  int u32 ;
struct mdp5_pipeline {scalar_t__ r_mixer; struct mdp5_interface* intf; } ;
struct mdp5_interface {int type; int /*<<< orphan*/  mode; scalar_t__ num; } ;
struct mdp5_ctl {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ INTF0 ; 
#define  INTF_DSI 129 
#define  INTF_WB 128 
 int MDP5_CTL_OP_CMD_MODE ; 
 int MDP5_CTL_OP_INTF_NUM (scalar_t__) ; 
 int MDP5_CTL_OP_MODE (int /*<<< orphan*/ ) ; 
 int MDP5_CTL_OP_PACK_3D (int) ; 
 int MDP5_CTL_OP_PACK_3D_ENABLE ; 
 int /*<<< orphan*/  MDP5_INTF_DSI_MODE_COMMAND ; 
 int /*<<< orphan*/  MDP5_INTF_WB_MODE_LINE ; 
 int /*<<< orphan*/  MODE_WB_2_LINE ; 
 int /*<<< orphan*/  REG_MDP5_CTL_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_write (struct mdp5_ctl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp5_cfg_intf_is_virtual (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void set_ctl_op(struct mdp5_ctl *ctl, struct mdp5_pipeline *pipeline)
{
	unsigned long flags;
	struct mdp5_interface *intf = pipeline->intf;
	u32 ctl_op = 0;

	if (!mdp5_cfg_intf_is_virtual(intf->type))
		ctl_op |= MDP5_CTL_OP_INTF_NUM(INTF0 + intf->num);

	switch (intf->type) {
	case INTF_DSI:
		if (intf->mode == MDP5_INTF_DSI_MODE_COMMAND)
			ctl_op |= MDP5_CTL_OP_CMD_MODE;
		break;

	case INTF_WB:
		if (intf->mode == MDP5_INTF_WB_MODE_LINE)
			ctl_op |= MDP5_CTL_OP_MODE(MODE_WB_2_LINE);
		break;

	default:
		break;
	}

	if (pipeline->r_mixer)
		ctl_op |= MDP5_CTL_OP_PACK_3D_ENABLE |
			  MDP5_CTL_OP_PACK_3D(1);

	spin_lock_irqsave(&ctl->hw_lock, flags);
	ctl_write(ctl, REG_MDP5_CTL_OP(ctl->id), ctl_op);
	spin_unlock_irqrestore(&ctl->hw_lock, flags);
}