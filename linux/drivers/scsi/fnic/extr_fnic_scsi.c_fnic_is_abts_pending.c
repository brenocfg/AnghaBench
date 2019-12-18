#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int dummy; } ;
struct scsi_cmnd {struct scsi_device* device; } ;
struct fnic_io_req {int dummy; } ;
struct fnic {int fnic_max_tag_id; TYPE_1__* lport; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ CMD_SP (struct scsi_cmnd*) ; 
 scalar_t__ CMD_STATE (struct scsi_cmnd*) ; 
 scalar_t__ FNIC_IOREQ_ABTS_PENDING ; 
 int /*<<< orphan*/  FNIC_SCSI_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/ * fnic_io_lock_hash (struct fnic*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  fnic_ioreq_state_to_str (scalar_t__) ; 
 struct scsi_cmnd* scsi_host_find_tag (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int fnic_is_abts_pending(struct fnic *fnic, struct scsi_cmnd *lr_sc)
{
	int tag;
	struct fnic_io_req *io_req;
	spinlock_t *io_lock;
	unsigned long flags;
	int ret = 0;
	struct scsi_cmnd *sc;
	struct scsi_device *lun_dev = NULL;

	if (lr_sc)
		lun_dev = lr_sc->device;

	/* walk again to check, if IOs are still pending in fw */
	for (tag = 0; tag < fnic->fnic_max_tag_id; tag++) {
		sc = scsi_host_find_tag(fnic->lport->host, tag);
		/*
		 * ignore this lun reset cmd or cmds that do not belong to
		 * this lun
		 */
		if (!sc || (lr_sc && (sc->device != lun_dev || sc == lr_sc)))
			continue;

		io_lock = fnic_io_lock_hash(fnic, sc);
		spin_lock_irqsave(io_lock, flags);

		io_req = (struct fnic_io_req *)CMD_SP(sc);

		if (!io_req || sc->device != lun_dev) {
			spin_unlock_irqrestore(io_lock, flags);
			continue;
		}

		/*
		 * Found IO that is still pending with firmware and
		 * belongs to the LUN that we are resetting
		 */
		FNIC_SCSI_DBG(KERN_INFO, fnic->lport->host,
			      "Found IO in %s on lun\n",
			      fnic_ioreq_state_to_str(CMD_STATE(sc)));

		if (CMD_STATE(sc) == FNIC_IOREQ_ABTS_PENDING)
			ret = 1;
		spin_unlock_irqrestore(io_lock, flags);
	}

	return ret;
}