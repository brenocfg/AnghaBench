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
struct qedi_ctx {int /*<<< orphan*/  nvm_buf_dma; scalar_t__ iscsi_image; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedi_free_nvm_iscsi_cfg(struct qedi_ctx *qedi)
{
	if (qedi->iscsi_image)
		dma_free_coherent(&qedi->pdev->dev,
				  sizeof(struct qedi_nvm_iscsi_image),
				  qedi->iscsi_image, qedi->nvm_buf_dma);
}