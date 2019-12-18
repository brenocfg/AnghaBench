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
struct qedi_nvm_iscsi_image {int dummy; } ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; scalar_t__ iscsi_image; int /*<<< orphan*/  cdev; } ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int (* nvm_get_image ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDI_LOG_INFO ; 
 int /*<<< orphan*/  QED_NVM_IMAGE_ISCSI_CFG ; 
 TYPE_2__* qedi_ops ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int qedi_get_boot_info(struct qedi_ctx *qedi)
{
	int ret = 1;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "Get NVM iSCSI CFG image\n");
	ret = qedi_ops->common->nvm_get_image(qedi->cdev,
					      QED_NVM_IMAGE_ISCSI_CFG,
					      (char *)qedi->iscsi_image,
					      sizeof(struct qedi_nvm_iscsi_image));
	if (ret)
		QEDI_ERR(&qedi->dbg_ctx,
			 "Could not get NVM image. ret = %d\n", ret);

	return ret;
}