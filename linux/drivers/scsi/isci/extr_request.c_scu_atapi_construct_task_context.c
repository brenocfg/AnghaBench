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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int /*<<< orphan*/  lbal; int /*<<< orphan*/  fis_type; } ;
struct TYPE_7__ {TYPE_5__ stp; } ;
struct scu_task_context {int sata_direction; int ssp_command_iu_length; int task_phase; int /*<<< orphan*/  transfer_length_bytes; scalar_t__ stp_retry_count; TYPE_2__ type; int /*<<< orphan*/  task_type; } ;
struct TYPE_9__ {int /*<<< orphan*/  atapi_packet; } ;
struct sas_task {scalar_t__ data_dir; int /*<<< orphan*/  total_xfer_len; TYPE_4__ ata_task; } ;
struct TYPE_8__ {TYPE_5__ cmd; } ;
struct isci_request {TYPE_3__ stp; struct scu_task_context* tc; TYPE_1__* target_device; } ;
struct ata_device {int cdb_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  domain_dev; } ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FIS_DATA ; 
 int /*<<< orphan*/  SCU_TASK_TYPE_PACKET_DMA_IN ; 
 int /*<<< orphan*/  SCU_TASK_TYPE_PACKET_DMA_OUT ; 
 struct sas_task* isci_request_access_task (struct isci_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 struct ata_device* sas_to_ata_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_request_build_sgl (struct isci_request*) ; 

__attribute__((used)) static void scu_atapi_construct_task_context(struct isci_request *ireq)
{
	struct ata_device *dev = sas_to_ata_dev(ireq->target_device->domain_dev);
	struct sas_task *task = isci_request_access_task(ireq);
	struct scu_task_context *task_context = ireq->tc;
	int cdb_len = dev->cdb_len;

	/* reference: SSTL 1.13.4.2
	 * task_type, sata_direction
	 */
	if (task->data_dir == DMA_TO_DEVICE) {
		task_context->task_type = SCU_TASK_TYPE_PACKET_DMA_OUT;
		task_context->sata_direction = 0;
	} else {
		/* todo: for NO_DATA command, we need to send out raw frame. */
		task_context->task_type = SCU_TASK_TYPE_PACKET_DMA_IN;
		task_context->sata_direction = 1;
	}

	memset(&task_context->type.stp, 0, sizeof(task_context->type.stp));
	task_context->type.stp.fis_type = FIS_DATA;

	memset(&ireq->stp.cmd, 0, sizeof(ireq->stp.cmd));
	memcpy(&ireq->stp.cmd.lbal, task->ata_task.atapi_packet, cdb_len);
	task_context->ssp_command_iu_length = cdb_len / sizeof(u32);

	/* task phase is set to TX_CMD */
	task_context->task_phase = 0x1;

	/* retry counter */
	task_context->stp_retry_count = 0;

	/* data transfer size. */
	task_context->transfer_length_bytes = task->total_xfer_len;

	/* setup sgl */
	sci_request_build_sgl(ireq);
}