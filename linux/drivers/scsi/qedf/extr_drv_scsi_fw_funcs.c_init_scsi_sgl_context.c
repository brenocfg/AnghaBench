#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  void* u32 ;
struct TYPE_7__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;
struct scsi_sgl_task_params {scalar_t__ num_sges; TYPE_5__* sgl; int /*<<< orphan*/  total_buffer_size; TYPE_1__ sgl_phys_addr; } ;
struct TYPE_8__ {void* hi; void* lo; } ;
struct scsi_sgl_params {int /*<<< orphan*/  sgl_num_sges; void* sgl_total_length; TYPE_2__ sgl_addr; } ;
struct scsi_cached_sges {TYPE_6__* sge; } ;
struct TYPE_10__ {void* hi; void* lo; } ;
struct TYPE_12__ {void* sge_len; TYPE_4__ sge_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;
struct TYPE_11__ {int /*<<< orphan*/  sge_len; TYPE_3__ sge_addr; } ;

/* Variables and functions */
 scalar_t__ SCSI_NUM_SGES_IN_CACHE ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

void init_scsi_sgl_context(struct scsi_sgl_params *ctx_sgl_params,
			   struct scsi_cached_sges *ctx_data_desc,
			   struct scsi_sgl_task_params *sgl_task_params)
{
	/* no need to check for sgl_task_params->sgl validity */
	u8 num_sges_to_init = sgl_task_params->num_sges >
			      SCSI_NUM_SGES_IN_CACHE ? SCSI_NUM_SGES_IN_CACHE :
			      sgl_task_params->num_sges;
	u8 sge_index;
	u32 val;

	val = cpu_to_le32(sgl_task_params->sgl_phys_addr.lo);
	ctx_sgl_params->sgl_addr.lo = val;
	val = cpu_to_le32(sgl_task_params->sgl_phys_addr.hi);
	ctx_sgl_params->sgl_addr.hi = val;
	val = cpu_to_le32(sgl_task_params->total_buffer_size);
	ctx_sgl_params->sgl_total_length = val;
	ctx_sgl_params->sgl_num_sges = cpu_to_le16(sgl_task_params->num_sges);

	for (sge_index = 0; sge_index < num_sges_to_init; sge_index++) {
		val = cpu_to_le32(sgl_task_params->sgl[sge_index].sge_addr.lo);
		ctx_data_desc->sge[sge_index].sge_addr.lo = val;
		val = cpu_to_le32(sgl_task_params->sgl[sge_index].sge_addr.hi);
		ctx_data_desc->sge[sge_index].sge_addr.hi = val;
		val = cpu_to_le32(sgl_task_params->sgl[sge_index].sge_len);
		ctx_data_desc->sge[sge_index].sge_len = val;
	}
}