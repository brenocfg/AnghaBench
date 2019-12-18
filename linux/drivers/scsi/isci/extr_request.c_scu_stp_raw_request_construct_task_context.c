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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  fis_type; } ;
struct TYPE_4__ {TYPE_1__ stp; } ;
struct scu_task_context {int transfer_length_bytes; TYPE_2__ type; int /*<<< orphan*/  task_type; int /*<<< orphan*/  priority; scalar_t__ control_frame; } ;
struct isci_request {struct scu_task_context* tc; } ;
struct host_to_dev_fis {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIS_REGH2D ; 
 int /*<<< orphan*/  SCU_TASK_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  SCU_TASK_TYPE_SATA_RAW_FRAME ; 
 int /*<<< orphan*/  scu_sata_request_construct_task_context (struct isci_request*,struct scu_task_context*) ; 

__attribute__((used)) static void scu_stp_raw_request_construct_task_context(struct isci_request *ireq)
{
	struct scu_task_context *task_context = ireq->tc;

	scu_sata_request_construct_task_context(ireq, task_context);

	task_context->control_frame         = 0;
	task_context->priority              = SCU_TASK_PRIORITY_NORMAL;
	task_context->task_type             = SCU_TASK_TYPE_SATA_RAW_FRAME;
	task_context->type.stp.fis_type     = FIS_REGH2D;
	task_context->transfer_length_bytes = sizeof(struct host_to_dev_fis) - sizeof(u32);
}