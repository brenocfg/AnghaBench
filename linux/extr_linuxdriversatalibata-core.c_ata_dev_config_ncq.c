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
struct ata_port {int flags; TYPE_2__* scsi_host; } ;
struct ata_device {int horkage; int /*<<< orphan*/  id; int /*<<< orphan*/  flags; TYPE_1__* link; } ;
struct TYPE_4__ {int /*<<< orphan*/  can_queue; } ;
struct TYPE_3__ {struct ata_port* ap; } ;

/* Variables and functions */
 unsigned int AC_ERR_DEV ; 
 int /*<<< orphan*/  ATA_DFLAG_NCQ ; 
 int ATA_FLAG_FPDMA_AA ; 
 int ATA_FLAG_FPDMA_AUX ; 
 int ATA_FLAG_NCQ ; 
 int ATA_HORKAGE_BROKEN_FPDMA_AA ; 
 int ATA_HORKAGE_NONCQ ; 
 int /*<<< orphan*/  ATA_MAX_QUEUE ; 
 int EIO ; 
 int /*<<< orphan*/  SATA_FPDMA_AA ; 
 int /*<<< orphan*/  SETFEATURES_SATA_ENABLE ; 
 int /*<<< orphan*/  ata_dev_config_ncq_non_data (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_config_ncq_prio (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_config_ncq_send_recv (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_err (struct ata_device*,char*,unsigned int) ; 
 unsigned int ata_dev_set_feature (struct ata_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_has_fpdma_aa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_id_has_ncq (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_has_ncq_non_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_has_ncq_prio (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_has_ncq_send_and_recv (int /*<<< orphan*/ ) ; 
 int ata_id_queue_depth (int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static int ata_dev_config_ncq(struct ata_device *dev,
			       char *desc, size_t desc_sz)
{
	struct ata_port *ap = dev->link->ap;
	int hdepth = 0, ddepth = ata_id_queue_depth(dev->id);
	unsigned int err_mask;
	char *aa_desc = "";

	if (!ata_id_has_ncq(dev->id)) {
		desc[0] = '\0';
		return 0;
	}
	if (dev->horkage & ATA_HORKAGE_NONCQ) {
		snprintf(desc, desc_sz, "NCQ (not used)");
		return 0;
	}
	if (ap->flags & ATA_FLAG_NCQ) {
		hdepth = min(ap->scsi_host->can_queue, ATA_MAX_QUEUE);
		dev->flags |= ATA_DFLAG_NCQ;
	}

	if (!(dev->horkage & ATA_HORKAGE_BROKEN_FPDMA_AA) &&
		(ap->flags & ATA_FLAG_FPDMA_AA) &&
		ata_id_has_fpdma_aa(dev->id)) {
		err_mask = ata_dev_set_feature(dev, SETFEATURES_SATA_ENABLE,
			SATA_FPDMA_AA);
		if (err_mask) {
			ata_dev_err(dev,
				    "failed to enable AA (error_mask=0x%x)\n",
				    err_mask);
			if (err_mask != AC_ERR_DEV) {
				dev->horkage |= ATA_HORKAGE_BROKEN_FPDMA_AA;
				return -EIO;
			}
		} else
			aa_desc = ", AA";
	}

	if (hdepth >= ddepth)
		snprintf(desc, desc_sz, "NCQ (depth %d)%s", ddepth, aa_desc);
	else
		snprintf(desc, desc_sz, "NCQ (depth %d/%d)%s", hdepth,
			ddepth, aa_desc);

	if ((ap->flags & ATA_FLAG_FPDMA_AUX)) {
		if (ata_id_has_ncq_send_and_recv(dev->id))
			ata_dev_config_ncq_send_recv(dev);
		if (ata_id_has_ncq_non_data(dev->id))
			ata_dev_config_ncq_non_data(dev);
		if (ata_id_has_ncq_prio(dev->id))
			ata_dev_config_ncq_prio(dev);
	}

	return 0;
}