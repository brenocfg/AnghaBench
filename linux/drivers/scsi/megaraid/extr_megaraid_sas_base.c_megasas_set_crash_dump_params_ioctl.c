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
struct megasas_instance {int crash_dump_app_support; TYPE_4__* pdev; int /*<<< orphan*/  adprecovery; scalar_t__ crash_dump_drv_support; } ;
struct megasas_cmd {TYPE_3__* frame; } ;
struct TYPE_10__ {int max_index; struct megasas_instance** instance; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int* w; } ;
struct TYPE_7__ {TYPE_1__ mbox; } ;
struct TYPE_8__ {TYPE_2__ dcmd; } ;

/* Variables and functions */
 scalar_t__ MEGASAS_HBA_OPERATIONAL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 TYPE_5__ megasas_mgmt_info ; 
 int /*<<< orphan*/  megasas_set_crash_dump_params (struct megasas_instance*,int) ; 

__attribute__((used)) static int megasas_set_crash_dump_params_ioctl(struct megasas_cmd *cmd)
{
	struct megasas_instance *local_instance;
	int i, error = 0;
	int crash_support;

	crash_support = cmd->frame->dcmd.mbox.w[0];

	for (i = 0; i < megasas_mgmt_info.max_index; i++) {
		local_instance = megasas_mgmt_info.instance[i];
		if (local_instance && local_instance->crash_dump_drv_support) {
			if ((atomic_read(&local_instance->adprecovery) ==
				MEGASAS_HBA_OPERATIONAL) &&
				!megasas_set_crash_dump_params(local_instance,
					crash_support)) {
				local_instance->crash_dump_app_support =
					crash_support;
				dev_info(&local_instance->pdev->dev,
					"Application firmware crash "
					"dump mode set success\n");
				error = 0;
			} else {
				dev_info(&local_instance->pdev->dev,
					"Application firmware crash "
					"dump mode set failed\n");
				error = -1;
			}
		}
	}
	return error;
}