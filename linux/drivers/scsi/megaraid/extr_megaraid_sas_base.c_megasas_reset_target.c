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
struct scsi_cmnd {TYPE_2__* device; } ;
struct megasas_instance {scalar_t__ adapter_type; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 scalar_t__ MFI_SERIES ; 
 int megasas_reset_target_fusion (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 

__attribute__((used)) static int megasas_reset_target(struct scsi_cmnd *scmd)
{
	int ret;
	struct megasas_instance *instance;

	instance = (struct megasas_instance *)scmd->device->host->hostdata;

	if (instance->adapter_type != MFI_SERIES)
		ret = megasas_reset_target_fusion(scmd);
	else {
		sdev_printk(KERN_NOTICE, scmd->device, "TARGET RESET not supported\n");
		ret = FAILED;
	}

	return ret;
}