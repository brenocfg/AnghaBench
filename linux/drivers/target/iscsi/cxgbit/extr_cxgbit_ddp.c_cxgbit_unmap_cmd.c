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
struct iscsi_conn {struct cxgbit_sock* context; } ;
struct TYPE_5__ {scalar_t__ data_length; } ;
struct iscsi_cmd {scalar_t__ write_data_done; TYPE_2__ se_cmd; } ;
struct TYPE_4__ {struct cxgbit_device* cdev; } ;
struct cxgbit_sock {TYPE_1__ com; } ;
struct cxgbit_device {int dummy; } ;
struct cxgbi_task_tag_info {int /*<<< orphan*/  nents; scalar_t__ sgl; int /*<<< orphan*/  idx; } ;
struct cxgbit_cmd {int release; int /*<<< orphan*/  sg; struct cxgbi_task_tag_info ttinfo; } ;
struct cxgbi_ppm {TYPE_3__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 struct cxgbi_ppm* cdev2ppm (struct cxgbit_device*) ; 
 int /*<<< orphan*/  cxgbi_ppm_ppod_release (struct cxgbi_ppm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbit_abort_conn (struct cxgbit_sock*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cxgbit_cmd* iscsit_priv_cmd (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void cxgbit_unmap_cmd(struct iscsi_conn *conn, struct iscsi_cmd *cmd)
{
	struct cxgbit_cmd *ccmd = iscsit_priv_cmd(cmd);

	if (ccmd->release) {
		struct cxgbi_task_tag_info *ttinfo = &ccmd->ttinfo;

		if (ttinfo->sgl) {
			struct cxgbit_sock *csk = conn->context;
			struct cxgbit_device *cdev = csk->com.cdev;
			struct cxgbi_ppm *ppm = cdev2ppm(cdev);

			/* Abort the TCP conn if DDP is not complete to
			 * avoid any possibility of DDP after freeing
			 * the cmd.
			 */
			if (unlikely(cmd->write_data_done !=
				     cmd->se_cmd.data_length))
				cxgbit_abort_conn(csk);

			cxgbi_ppm_ppod_release(ppm, ttinfo->idx);

			dma_unmap_sg(&ppm->pdev->dev, ttinfo->sgl,
				     ttinfo->nents, DMA_FROM_DEVICE);
		} else {
			put_page(sg_page(&ccmd->sg));
		}

		ccmd->release = false;
	}
}