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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; } ;
struct bfa_bsg_port_cfg_s {int /*<<< orphan*/  status; int /*<<< orphan*/  param; } ;

/* Variables and functions */
 unsigned int IOCMD_PORT_CFG_ALPA ; 
 unsigned int IOCMD_PORT_CFG_SPEED ; 
 unsigned int IOCMD_PORT_CFG_TOPO ; 
 unsigned int IOCMD_PORT_CLR_ALPA ; 
 int /*<<< orphan*/  bfa_fcport_cfg_hardalpa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_cfg_speed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_cfg_topology (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_clr_hardalpa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_set_port_cfg(struct bfad_s *bfad, void *iocmd, unsigned int v_cmd)
{
	struct bfa_bsg_port_cfg_s *cmd = (struct bfa_bsg_port_cfg_s *)iocmd;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	if (v_cmd == IOCMD_PORT_CFG_TOPO)
		cmd->status = bfa_fcport_cfg_topology(&bfad->bfa, cmd->param);
	else if (v_cmd == IOCMD_PORT_CFG_SPEED)
		cmd->status = bfa_fcport_cfg_speed(&bfad->bfa, cmd->param);
	else if (v_cmd == IOCMD_PORT_CFG_ALPA)
		cmd->status = bfa_fcport_cfg_hardalpa(&bfad->bfa, cmd->param);
	else if (v_cmd == IOCMD_PORT_CLR_ALPA)
		cmd->status = bfa_fcport_clr_hardalpa(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return 0;
}