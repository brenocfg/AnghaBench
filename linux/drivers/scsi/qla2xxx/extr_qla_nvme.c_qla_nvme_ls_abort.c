#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvmefc_ls_req {struct nvme_private* private; } ;
struct nvme_private {int /*<<< orphan*/  abort_work; int /*<<< orphan*/  cmd_lock; TYPE_1__* sp; } ;
struct nvme_fc_remote_port {int dummy; } ;
struct nvme_fc_local_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_nvme_abort_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qla_nvme_ls_abort(struct nvme_fc_local_port *lport,
    struct nvme_fc_remote_port *rport, struct nvmefc_ls_req *fd)
{
	struct nvme_private *priv = fd->private;
	unsigned long flags;

	spin_lock_irqsave(&priv->cmd_lock, flags);
	if (!priv->sp) {
		spin_unlock_irqrestore(&priv->cmd_lock, flags);
		return;
	}

	if (!kref_get_unless_zero(&priv->sp->cmd_kref)) {
		spin_unlock_irqrestore(&priv->cmd_lock, flags);
		return;
	}
	spin_unlock_irqrestore(&priv->cmd_lock, flags);

	INIT_WORK(&priv->abort_work, qla_nvme_abort_work);
	schedule_work(&priv->abort_work);
}