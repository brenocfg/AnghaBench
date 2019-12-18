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
struct nvme_private {int comp_status; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd_kref; struct nvme_private* priv; } ;
typedef  TYPE_1__ srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_nvme_release_fcp_cmd_kref ; 

__attribute__((used)) static void qla_nvme_sp_done(srb_t *sp, int res)
{
	struct nvme_private *priv = sp->priv;

	priv->comp_status = res;
	kref_put(&sp->cmd_kref, qla_nvme_release_fcp_cmd_kref);

	return;
}