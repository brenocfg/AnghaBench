#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvme_private {int comp_status; int /*<<< orphan*/  ls_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd_kref; struct nvme_private* priv; } ;
typedef  TYPE_1__ srb_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_nvme_ls_complete ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla_nvme_sp_ls_done(srb_t *sp, int res)
{
	struct nvme_private *priv = sp->priv;

	if (WARN_ON_ONCE(kref_read(&sp->cmd_kref) == 0))
		return;

	if (res)
		res = -EINVAL;

	priv->comp_status = res;
	INIT_WORK(&priv->ls_work, qla_nvme_ls_complete);
	schedule_work(&priv->ls_work);
}