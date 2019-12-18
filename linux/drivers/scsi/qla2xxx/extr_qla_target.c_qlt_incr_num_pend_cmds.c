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
struct TYPE_4__ {scalar_t__ stat_max_pend_cmds; } ;
struct scsi_qla_host {TYPE_3__* hw; TYPE_1__ qla_stats; } ;
struct TYPE_5__ {scalar_t__ num_pend_cmds; int /*<<< orphan*/  q_full_lock; } ;
struct TYPE_6__ {TYPE_2__ tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void qlt_incr_num_pend_cmds(struct scsi_qla_host *vha)
{
	unsigned long flags;

	spin_lock_irqsave(&vha->hw->tgt.q_full_lock, flags);

	vha->hw->tgt.num_pend_cmds++;
	if (vha->hw->tgt.num_pend_cmds > vha->qla_stats.stat_max_pend_cmds)
		vha->qla_stats.stat_max_pend_cmds =
			vha->hw->tgt.num_pend_cmds;
	spin_unlock_irqrestore(&vha->hw->tgt.q_full_lock, flags);
}