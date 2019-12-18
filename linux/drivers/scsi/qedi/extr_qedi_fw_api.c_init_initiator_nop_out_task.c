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
struct scsi_sgl_task_params {int /*<<< orphan*/  total_buffer_size; } ;
struct iscsi_task_params {scalar_t__ rx_io_size; scalar_t__ tx_io_size; struct e4_iscsi_task_context* context; } ;
struct iscsi_nop_out_hdr {scalar_t__ itt; } ;
struct iscsi_common_hdr {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rem_task_size; int /*<<< orphan*/  data_desc; int /*<<< orphan*/  sgl_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_desc; int /*<<< orphan*/  sgl_params; } ;
struct TYPE_5__ {TYPE_1__ state; } ;
struct e4_iscsi_task_context {TYPE_3__ mstorm_st_context; int /*<<< orphan*/  ustorm_ag_context; int /*<<< orphan*/  ustorm_st_context; TYPE_2__ ystorm_st_context; } ;
struct data_hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISCSI_ITT_ALL_ONES ; 
 int /*<<< orphan*/  ISCSI_TASK_TYPE_MIDPATH ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_default_iscsi_task (struct iscsi_task_params*,struct data_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_scsi_sgl_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct scsi_sgl_task_params*) ; 
 int /*<<< orphan*/  init_sqe (struct iscsi_task_params*,struct scsi_sgl_task_params*,int /*<<< orphan*/ *,struct iscsi_common_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_ustorm_task_contexts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_local_completion_context (struct e4_iscsi_task_context*) ; 

int init_initiator_nop_out_task(struct iscsi_task_params *task_params,
				struct iscsi_nop_out_hdr *nop_out_pdu_header,
				struct scsi_sgl_task_params *tx_sgl_task_params,
				struct scsi_sgl_task_params *rx_sgl_task_params)
{
	struct e4_iscsi_task_context *cxt;

	cxt = task_params->context;

	init_default_iscsi_task(task_params,
				(struct data_hdr *)nop_out_pdu_header,
				ISCSI_TASK_TYPE_MIDPATH);

	if (nop_out_pdu_header->itt == ISCSI_ITT_ALL_ONES)
		set_local_completion_context(task_params->context);

	if (task_params->tx_io_size)
		init_scsi_sgl_context(&cxt->ystorm_st_context.state.sgl_params,
				      &cxt->ystorm_st_context.state.data_desc,
				      tx_sgl_task_params);

	if (task_params->rx_io_size)
		init_scsi_sgl_context(&cxt->mstorm_st_context.sgl_params,
				      &cxt->mstorm_st_context.data_desc,
				      rx_sgl_task_params);

	init_ustorm_task_contexts(&cxt->ustorm_st_context,
				  &cxt->ustorm_ag_context,
				  task_params->rx_io_size ?
				  rx_sgl_task_params->total_buffer_size : 0,
				  task_params->tx_io_size ?
				  tx_sgl_task_params->total_buffer_size : 0,
				  0, 0);

	cxt->mstorm_st_context.rem_task_size =
				cpu_to_le32(task_params->rx_io_size ?
					rx_sgl_task_params->total_buffer_size :
					0);

	init_sqe(task_params, tx_sgl_task_params, NULL,
		 (struct iscsi_common_hdr *)nop_out_pdu_header, NULL,
		 ISCSI_TASK_TYPE_MIDPATH, false);

	return 0;
}