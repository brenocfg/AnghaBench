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
struct mtk_mdp_vpu {int /*<<< orphan*/  pdev; } ;
struct mtk_mdp_ctx {TYPE_2__* mdp_dev; int /*<<< orphan*/  id; } ;
typedef  enum ipi_id { ____Placeholder_ipi_id } ipi_id ;
struct TYPE_4__ {int /*<<< orphan*/  vpulock; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mtk_mdp_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vpu_ipi_send (int /*<<< orphan*/ ,int,void*,int) ; 
 struct mtk_mdp_ctx* vpu_to_ctx (struct mtk_mdp_vpu*) ; 

__attribute__((used)) static int mtk_mdp_vpu_send_msg(void *msg, int len, struct mtk_mdp_vpu *vpu,
				int id)
{
	struct mtk_mdp_ctx *ctx = vpu_to_ctx(vpu);
	int err;

	if (!vpu->pdev) {
		mtk_mdp_dbg(1, "[%d]:vpu pdev is NULL", ctx->id);
		return -EINVAL;
	}

	mutex_lock(&ctx->mdp_dev->vpulock);
	err = vpu_ipi_send(vpu->pdev, (enum ipi_id)id, msg, len);
	if (err)
		dev_err(&ctx->mdp_dev->pdev->dev,
			"vpu_ipi_send fail status %d\n", err);
	mutex_unlock(&ctx->mdp_dev->vpulock);

	return err;
}