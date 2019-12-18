#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort ;
struct scsi_device {int id; scalar_t__ lun; scalar_t__ tagged_supported; scalar_t__ sdtr; } ;
struct TYPE_6__ {int use_tagged_qng; int init_sdtr; int* max_dvc_qng; int /*<<< orphan*/  iop_base; TYPE_1__* cfg; } ;
struct TYPE_5__ {int sdtr_enable; int cmd_qng_enabled; int can_tagged_qng; int disc_enable; int* max_tag_qng; } ;
typedef  int ASC_SCSI_BIT_ID_TYPE ;
typedef  TYPE_2__ ASC_DVC_VAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASCV_CAN_TAGGED_QNG_B ; 
 int /*<<< orphan*/  ASCV_DISC_ENABLE_B ; 
 scalar_t__ ASCV_MAX_DVC_QNG_BEG ; 
 int /*<<< orphan*/  ASCV_USE_TAGGED_QNG_B ; 
 int /*<<< orphan*/  AscAsyncFix (TYPE_2__*,struct scsi_device*) ; 
 int /*<<< orphan*/  AscWriteLramByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,int) ; 

__attribute__((used)) static void
advansys_narrow_slave_configure(struct scsi_device *sdev, ASC_DVC_VAR *asc_dvc)
{
	ASC_SCSI_BIT_ID_TYPE tid_bit = 1 << sdev->id;
	ASC_SCSI_BIT_ID_TYPE orig_use_tagged_qng = asc_dvc->use_tagged_qng;

	if (sdev->lun == 0) {
		ASC_SCSI_BIT_ID_TYPE orig_init_sdtr = asc_dvc->init_sdtr;
		if ((asc_dvc->cfg->sdtr_enable & tid_bit) && sdev->sdtr) {
			asc_dvc->init_sdtr |= tid_bit;
		} else {
			asc_dvc->init_sdtr &= ~tid_bit;
		}

		if (orig_init_sdtr != asc_dvc->init_sdtr)
			AscAsyncFix(asc_dvc, sdev);
	}

	if (sdev->tagged_supported) {
		if (asc_dvc->cfg->cmd_qng_enabled & tid_bit) {
			if (sdev->lun == 0) {
				asc_dvc->cfg->can_tagged_qng |= tid_bit;
				asc_dvc->use_tagged_qng |= tid_bit;
			}
			scsi_change_queue_depth(sdev, 
						asc_dvc->max_dvc_qng[sdev->id]);
		}
	} else {
		if (sdev->lun == 0) {
			asc_dvc->cfg->can_tagged_qng &= ~tid_bit;
			asc_dvc->use_tagged_qng &= ~tid_bit;
		}
	}

	if ((sdev->lun == 0) &&
	    (orig_use_tagged_qng != asc_dvc->use_tagged_qng)) {
		AscWriteLramByte(asc_dvc->iop_base, ASCV_DISC_ENABLE_B,
				 asc_dvc->cfg->disc_enable);
		AscWriteLramByte(asc_dvc->iop_base, ASCV_USE_TAGGED_QNG_B,
				 asc_dvc->use_tagged_qng);
		AscWriteLramByte(asc_dvc->iop_base, ASCV_CAN_TAGGED_QNG_B,
				 asc_dvc->cfg->can_tagged_qng);

		asc_dvc->max_dvc_qng[sdev->id] =
					asc_dvc->cfg->max_tag_qng[sdev->id];
		AscWriteLramByte(asc_dvc->iop_base,
				 (ushort)(ASCV_MAX_DVC_QNG_BEG + sdev->id),
				 asc_dvc->max_dvc_qng[sdev->id]);
	}
}