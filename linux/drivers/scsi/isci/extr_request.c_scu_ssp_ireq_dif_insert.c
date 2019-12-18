#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {int op; } ;
struct scu_task_context {int block_guard_enable; int blk_prot_en; int blk_sz; int blk_prot_func; int DIF_bytes_immed_val; int ref_tag_seed_gen; scalar_t__ reserved_E8_0; scalar_t__ blk_guard_err; scalar_t__ app_tag_verify_mask; TYPE_3__ bgctl_f; scalar_t__ bgctl; scalar_t__ app_tag_gen_mask; scalar_t__ reserved_E0_0; int /*<<< orphan*/  bgc_blk_sz; scalar_t__ reserved_DC_1; scalar_t__ reserved_DC_0; int /*<<< orphan*/  UD_bytes_immed_val; scalar_t__ ref_tag_seed_verify; scalar_t__ app_tag_gen; scalar_t__ app_tag_verify; scalar_t__ init_crc_seed; scalar_t__ interm_crc_val; int /*<<< orphan*/  transfer_length_bytes; } ;
struct scsi_cmnd {TYPE_4__* device; } ;
struct TYPE_6__ {TYPE_1__* io_task_ptr; } ;
struct isci_request {TYPE_2__ ttype_ptr; struct scu_task_context* tc; } ;
struct TYPE_8__ {int /*<<< orphan*/  sector_size; } ;
struct TYPE_5__ {struct scsi_cmnd* uldd_task; } ;

/* Variables and functions */
 int SCSI_PROT_DIF_TYPE1 ; 
 int SCSI_PROT_DIF_TYPE2 ; 
 int SCSI_PROT_DIF_TYPE3 ; 
 int scsi_get_lba (struct scsi_cmnd*) ; 
 int scu_bg_blk_size (TYPE_4__*) ; 
 scalar_t__ scu_dif_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scu_ssp_ireq_dif_insert(struct isci_request *ireq, u8 type, u8 op)
{
	struct scu_task_context *tc = ireq->tc;
	struct scsi_cmnd *scmd = ireq->ttype_ptr.io_task_ptr->uldd_task;
	u8 blk_sz = scu_bg_blk_size(scmd->device);

	tc->block_guard_enable = 1;
	tc->blk_prot_en = 1;
	tc->blk_sz = blk_sz;
	/* DIF write insert */
	tc->blk_prot_func = 0x2;

	tc->transfer_length_bytes += scu_dif_bytes(tc->transfer_length_bytes,
						   scmd->device->sector_size);

	/* always init to 0, used by hw */
	tc->interm_crc_val = 0;

	tc->init_crc_seed = 0;
	tc->app_tag_verify = 0;
	tc->app_tag_gen = 0;
	tc->ref_tag_seed_verify = 0;

	/* always init to same as bg_blk_sz */
	tc->UD_bytes_immed_val = scmd->device->sector_size;

	tc->reserved_DC_0 = 0;

	/* always init to 8 */
	tc->DIF_bytes_immed_val = 8;

	tc->reserved_DC_1 = 0;
	tc->bgc_blk_sz = scmd->device->sector_size;
	tc->reserved_E0_0 = 0;
	tc->app_tag_gen_mask = 0;

	/** setup block guard control **/
	tc->bgctl = 0;

	/* DIF write insert */
	tc->bgctl_f.op = 0x2;

	tc->app_tag_verify_mask = 0;

	/* must init to 0 for hw */
	tc->blk_guard_err = 0;

	tc->reserved_E8_0 = 0;

	if ((type & SCSI_PROT_DIF_TYPE1) || (type & SCSI_PROT_DIF_TYPE2))
		tc->ref_tag_seed_gen = scsi_get_lba(scmd) & 0xffffffff;
	else if (type & SCSI_PROT_DIF_TYPE3)
		tc->ref_tag_seed_gen = 0;
}