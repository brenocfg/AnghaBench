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
struct TYPE_4__ {void* hw_block_size; scalar_t__ hw_queue_depth; void* hw_max_sectors; } ;
struct se_device {TYPE_2__ dev_attrib; int /*<<< orphan*/  t10_wwn; } ;
struct scsi_device {scalar_t__ type; void* sector_size; scalar_t__ queue_depth; TYPE_1__* host; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; struct request_queue* request_queue; } ;
struct request_queue {int dummy; } ;
struct pscsi_dev_virt {struct scsi_device* pdv_sd; } ;
struct TYPE_3__ {int max_sectors; } ;

/* Variables and functions */
 scalar_t__ PSCSI_DEFAULT_QUEUEDEPTH ; 
 struct pscsi_dev_virt* PSCSI_DEV (struct se_device*) ; 
 scalar_t__ TYPE_TAPE ; 
 void* min_not_zero (int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pscsi_get_inquiry_vpd_device_ident (struct scsi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pscsi_get_inquiry_vpd_serial (struct scsi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pscsi_set_inquiry_info (struct scsi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pscsi_tape_read_blocksize (struct se_device*,struct scsi_device*) ; 
 int queue_max_hw_sectors (struct request_queue*) ; 

__attribute__((used)) static int pscsi_add_device_to_list(struct se_device *dev,
		struct scsi_device *sd)
{
	struct pscsi_dev_virt *pdv = PSCSI_DEV(dev);
	struct request_queue *q = sd->request_queue;

	pdv->pdv_sd = sd;

	if (!sd->queue_depth) {
		sd->queue_depth = PSCSI_DEFAULT_QUEUEDEPTH;

		pr_err("Set broken SCSI Device %d:%d:%llu"
			" queue_depth to %d\n", sd->channel, sd->id,
				sd->lun, sd->queue_depth);
	}

	dev->dev_attrib.hw_block_size =
		min_not_zero((int)sd->sector_size, 512);
	dev->dev_attrib.hw_max_sectors =
		min_not_zero(sd->host->max_sectors, queue_max_hw_sectors(q));
	dev->dev_attrib.hw_queue_depth = sd->queue_depth;

	/*
	 * Setup our standard INQUIRY info into se_dev->t10_wwn
	 */
	pscsi_set_inquiry_info(sd, &dev->t10_wwn);

	/*
	 * Locate VPD WWN Information used for various purposes within
	 * the Storage Engine.
	 */
	if (!pscsi_get_inquiry_vpd_serial(sd, &dev->t10_wwn)) {
		/*
		 * If VPD Unit Serial returned GOOD status, try
		 * VPD Device Identification page (0x83).
		 */
		pscsi_get_inquiry_vpd_device_ident(sd, &dev->t10_wwn);
	}

	/*
	 * For TYPE_TAPE, attempt to determine blocksize with MODE_SENSE.
	 */
	if (sd->type == TYPE_TAPE) {
		pscsi_tape_read_blocksize(dev, sd);
		dev->dev_attrib.hw_block_size = sd->sector_size;
	}
	return 0;
}