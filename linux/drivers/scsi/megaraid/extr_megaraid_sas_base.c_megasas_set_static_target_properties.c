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
typedef  int u32 ;
struct scsi_device {int /*<<< orphan*/  request_queue; TYPE_1__* host; } ;
struct megasas_instance {scalar_t__ nvme_page_size; TYPE_2__* tgt_prop; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_io_size_kb; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int HZ ; 
 int MR_DEFAULT_NVME_MDTS_KB ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct megasas_instance* megasas_lookup_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_set_fw_assisted_qd (struct scsi_device*,int) ; 
 int /*<<< orphan*/  megasas_set_nvme_device_properties (struct scsi_device*,int) ; 
 int scmd_timeout ; 

__attribute__((used)) static void megasas_set_static_target_properties(struct scsi_device *sdev,
						 bool is_target_prop)
{
	u32 max_io_size_kb = MR_DEFAULT_NVME_MDTS_KB;
	struct megasas_instance *instance;

	instance = megasas_lookup_instance(sdev->host->host_no);

	/*
	 * The RAID firmware may require extended timeouts.
	 */
	blk_queue_rq_timeout(sdev->request_queue, scmd_timeout * HZ);

	/* max_io_size_kb will be set to non zero for
	 * nvme based vd and syspd.
	 */
	if (is_target_prop)
		max_io_size_kb = le32_to_cpu(instance->tgt_prop->max_io_size_kb);

	if (instance->nvme_page_size && max_io_size_kb)
		megasas_set_nvme_device_properties(sdev, (max_io_size_kb << 10));

	megasas_set_fw_assisted_qd(sdev, is_target_prop);
}