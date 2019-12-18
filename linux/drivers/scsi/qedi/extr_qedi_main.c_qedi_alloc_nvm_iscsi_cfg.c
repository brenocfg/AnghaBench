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
struct qedi_nvm_iscsi_image {int dummy; } ;
struct qedi_ctx {int /*<<< orphan*/  nvm_buf_dma; int /*<<< orphan*/  iscsi_image; int /*<<< orphan*/  dbg_ctx; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDI_LOG_INFO ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedi_alloc_nvm_iscsi_cfg(struct qedi_ctx *qedi)
{
	qedi->iscsi_image = dma_alloc_coherent(&qedi->pdev->dev,
					       sizeof(struct qedi_nvm_iscsi_image),
					       &qedi->nvm_buf_dma, GFP_KERNEL);
	if (!qedi->iscsi_image) {
		QEDI_ERR(&qedi->dbg_ctx, "Could not allocate NVM BUF.\n");
		return -ENOMEM;
	}
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "NVM BUF addr=0x%p dma=0x%llx.\n", qedi->iscsi_image,
		  qedi->nvm_buf_dma);

	return 0;
}