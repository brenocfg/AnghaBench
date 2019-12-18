#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; } ;
struct TYPE_10__ {int /*<<< orphan*/  qos_bw_op; int /*<<< orphan*/  total_bb_cr; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int /*<<< orphan*/  low; int /*<<< orphan*/  med; int /*<<< orphan*/  high; } ;
struct TYPE_8__ {scalar_t__ topology; TYPE_2__ qos_bw; } ;
struct bfa_fcport_s {scalar_t__ topology; TYPE_5__ qos_attr; TYPE_3__ cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  low; int /*<<< orphan*/  med; int /*<<< orphan*/  high; } ;
struct TYPE_9__ {int /*<<< orphan*/  qos_bw_op; TYPE_1__ qos_bw; int /*<<< orphan*/  total_bb_cr; int /*<<< orphan*/  state; } ;
struct bfa_bsg_qos_attr_s {int /*<<< orphan*/  status; TYPE_4__ attr; } ;

/* Variables and functions */
 struct bfa_fcport_s* BFA_FCPORT_MOD (int /*<<< orphan*/ *) ; 
 scalar_t__ BFA_PORT_TOPOLOGY_LOOP ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_STATUS_TOPOLOGY_LOOP ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_qos_get_attr(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_qos_attr_s *iocmd = (struct bfa_bsg_qos_attr_s *)cmd;
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	if ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) &&
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
		iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
	else {
		iocmd->attr.state = fcport->qos_attr.state;
		iocmd->attr.total_bb_cr =
			be32_to_cpu(fcport->qos_attr.total_bb_cr);
		iocmd->attr.qos_bw.high = fcport->cfg.qos_bw.high;
		iocmd->attr.qos_bw.med = fcport->cfg.qos_bw.med;
		iocmd->attr.qos_bw.low = fcport->cfg.qos_bw.low;
		iocmd->attr.qos_bw_op = fcport->qos_attr.qos_bw_op;
		iocmd->status = BFA_STATUS_OK;
	}
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return 0;
}