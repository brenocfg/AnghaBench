#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct us_data {int (* transport ) (struct scsi_cmnd*,struct us_data*) ;scalar_t__ protocol; int fflags; scalar_t__ subclass; int /*<<< orphan*/  dflags; int /*<<< orphan*/  (* transport_reset ) (struct us_data*) ;int /*<<< orphan*/  dev_mutex; struct scsi_cmnd* srb; } ;
struct scsi_sense_hdr {int response_code; scalar_t__ asc; scalar_t__ ascq; int /*<<< orphan*/  sense_key; } ;
struct scsi_eh_save {int dummy; } ;
struct scsi_cmnd {int result; scalar_t__ sc_data_direction; int* cmnd; int cmd_len; int* sense_buffer; scalar_t__ underflow; } ;

/* Variables and functions */
 int ATA_12 ; 
 int ATA_16 ; 
 int DID_ABORT ; 
 int DID_ERROR ; 
 int DID_IMM_RETRY ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 void* HARDWARE_ERROR ; 
 int INQUIRY ; 
 int LOG_SENSE ; 
 int MODE_SENSE ; 
 int MODE_SENSE_10 ; 
 int READ_10 ; 
 int REQUEST_SENSE ; 
 void* SAM_STAT_CHECK_CONDITION ; 
 void* SAM_STAT_GOOD ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 scalar_t__ USB_PR_CB ; 
 scalar_t__ USB_PR_DPCM_USB ; 
 scalar_t__ USB_SC_CYP_ATACB ; 
 scalar_t__ USB_SC_RBC ; 
 scalar_t__ USB_SC_SCSI ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_FAILED ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_TRANSPORT_NO_SENSE ; 
 int /*<<< orphan*/  US_FLIDX_ABORTING ; 
 int /*<<< orphan*/  US_FLIDX_READ10_WORKED ; 
 int /*<<< orphan*/  US_FLIDX_REDO_READ10 ; 
 int /*<<< orphan*/  US_FLIDX_RESETTING ; 
 int /*<<< orphan*/  US_FLIDX_TIMED_OUT ; 
 int US_FL_BAD_SENSE ; 
 int US_FL_INITIAL_READ10 ; 
 int US_FL_SANE_SENSE ; 
 int US_FL_SCM_MULT_TARG ; 
 int US_SENSE_SIZE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  last_sector_hacks (struct us_data*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_eh_prep_cmnd (struct scsi_cmnd*,struct scsi_eh_save*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_eh_restore_cmnd (struct scsi_cmnd*,struct scsi_eh_save*) ; 
 scalar_t__ scsi_get_resid (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_normalize_sense (int*,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 int* scsi_sense_desc_find (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct scsi_cmnd*,struct us_data*) ; 
 int stub2 (struct scsi_cmnd*,struct us_data*) ; 
 int /*<<< orphan*/  stub3 (struct us_data*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  us_to_host (struct us_data*) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 
 int usb_stor_port_reset (struct us_data*) ; 
 int /*<<< orphan*/  usb_stor_report_device_reset (struct us_data*) ; 
 int /*<<< orphan*/  usb_stor_show_sense (struct us_data*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void usb_stor_invoke_transport(struct scsi_cmnd *srb, struct us_data *us)
{
	int need_auto_sense;
	int result;

	/* send the command to the transport layer */
	scsi_set_resid(srb, 0);
	result = us->transport(srb, us);

	/*
	 * if the command gets aborted by the higher layers, we need to
	 * short-circuit all other processing
	 */
	if (test_bit(US_FLIDX_TIMED_OUT, &us->dflags)) {
		usb_stor_dbg(us, "-- command was aborted\n");
		srb->result = DID_ABORT << 16;
		goto Handle_Errors;
	}

	/* if there is a transport error, reset and don't auto-sense */
	if (result == USB_STOR_TRANSPORT_ERROR) {
		usb_stor_dbg(us, "-- transport indicates error, resetting\n");
		srb->result = DID_ERROR << 16;
		goto Handle_Errors;
	}

	/* if the transport provided its own sense data, don't auto-sense */
	if (result == USB_STOR_TRANSPORT_NO_SENSE) {
		srb->result = SAM_STAT_CHECK_CONDITION;
		last_sector_hacks(us, srb);
		return;
	}

	srb->result = SAM_STAT_GOOD;

	/*
	 * Determine if we need to auto-sense
	 *
	 * I normally don't use a flag like this, but it's almost impossible
	 * to understand what's going on here if I don't.
	 */
	need_auto_sense = 0;

	/*
	 * If we're running the CB transport, which is incapable
	 * of determining status on its own, we will auto-sense
	 * unless the operation involved a data-in transfer.  Devices
	 * can signal most data-in errors by stalling the bulk-in pipe.
	 */
	if ((us->protocol == USB_PR_CB || us->protocol == USB_PR_DPCM_USB) &&
			srb->sc_data_direction != DMA_FROM_DEVICE) {
		usb_stor_dbg(us, "-- CB transport device requiring auto-sense\n");
		need_auto_sense = 1;
	}

	/*
	 * If we have a failure, we're going to do a REQUEST_SENSE 
	 * automatically.  Note that we differentiate between a command
	 * "failure" and an "error" in the transport mechanism.
	 */
	if (result == USB_STOR_TRANSPORT_FAILED) {
		usb_stor_dbg(us, "-- transport indicates command failure\n");
		need_auto_sense = 1;
	}

	/*
	 * Determine if this device is SAT by seeing if the
	 * command executed successfully.  Otherwise we'll have
	 * to wait for at least one CHECK_CONDITION to determine
	 * SANE_SENSE support
	 */
	if (unlikely((srb->cmnd[0] == ATA_16 || srb->cmnd[0] == ATA_12) &&
	    result == USB_STOR_TRANSPORT_GOOD &&
	    !(us->fflags & US_FL_SANE_SENSE) &&
	    !(us->fflags & US_FL_BAD_SENSE) &&
	    !(srb->cmnd[2] & 0x20))) {
		usb_stor_dbg(us, "-- SAT supported, increasing auto-sense\n");
		us->fflags |= US_FL_SANE_SENSE;
	}

	/*
	 * A short transfer on a command where we don't expect it
	 * is unusual, but it doesn't mean we need to auto-sense.
	 */
	if ((scsi_get_resid(srb) > 0) &&
	    !((srb->cmnd[0] == REQUEST_SENSE) ||
	      (srb->cmnd[0] == INQUIRY) ||
	      (srb->cmnd[0] == MODE_SENSE) ||
	      (srb->cmnd[0] == LOG_SENSE) ||
	      (srb->cmnd[0] == MODE_SENSE_10))) {
		usb_stor_dbg(us, "-- unexpectedly short transfer\n");
	}

	/* Now, if we need to do the auto-sense, let's do it */
	if (need_auto_sense) {
		int temp_result;
		struct scsi_eh_save ses;
		int sense_size = US_SENSE_SIZE;
		struct scsi_sense_hdr sshdr;
		const u8 *scdd;
		u8 fm_ili;

		/* device supports and needs bigger sense buffer */
		if (us->fflags & US_FL_SANE_SENSE)
			sense_size = ~0;
Retry_Sense:
		usb_stor_dbg(us, "Issuing auto-REQUEST_SENSE\n");

		scsi_eh_prep_cmnd(srb, &ses, NULL, 0, sense_size);

		/* FIXME: we must do the protocol translation here */
		if (us->subclass == USB_SC_RBC || us->subclass == USB_SC_SCSI ||
				us->subclass == USB_SC_CYP_ATACB)
			srb->cmd_len = 6;
		else
			srb->cmd_len = 12;

		/* issue the auto-sense command */
		scsi_set_resid(srb, 0);
		temp_result = us->transport(us->srb, us);

		/* let's clean up right away */
		scsi_eh_restore_cmnd(srb, &ses);

		if (test_bit(US_FLIDX_TIMED_OUT, &us->dflags)) {
			usb_stor_dbg(us, "-- auto-sense aborted\n");
			srb->result = DID_ABORT << 16;

			/* If SANE_SENSE caused this problem, disable it */
			if (sense_size != US_SENSE_SIZE) {
				us->fflags &= ~US_FL_SANE_SENSE;
				us->fflags |= US_FL_BAD_SENSE;
			}
			goto Handle_Errors;
		}

		/*
		 * Some devices claim to support larger sense but fail when
		 * trying to request it. When a transport failure happens
		 * using US_FS_SANE_SENSE, we always retry with a standard
		 * (small) sense request. This fixes some USB GSM modems
		 */
		if (temp_result == USB_STOR_TRANSPORT_FAILED &&
				sense_size != US_SENSE_SIZE) {
			usb_stor_dbg(us, "-- auto-sense failure, retry small sense\n");
			sense_size = US_SENSE_SIZE;
			us->fflags &= ~US_FL_SANE_SENSE;
			us->fflags |= US_FL_BAD_SENSE;
			goto Retry_Sense;
		}

		/* Other failures */
		if (temp_result != USB_STOR_TRANSPORT_GOOD) {
			usb_stor_dbg(us, "-- auto-sense failure\n");

			/*
			 * we skip the reset if this happens to be a
			 * multi-target device, since failure of an
			 * auto-sense is perfectly valid
			 */
			srb->result = DID_ERROR << 16;
			if (!(us->fflags & US_FL_SCM_MULT_TARG))
				goto Handle_Errors;
			return;
		}

		/*
		 * If the sense data returned is larger than 18-bytes then we
		 * assume this device supports requesting more in the future.
		 * The response code must be 70h through 73h inclusive.
		 */
		if (srb->sense_buffer[7] > (US_SENSE_SIZE - 8) &&
		    !(us->fflags & US_FL_SANE_SENSE) &&
		    !(us->fflags & US_FL_BAD_SENSE) &&
		    (srb->sense_buffer[0] & 0x7C) == 0x70) {
			usb_stor_dbg(us, "-- SANE_SENSE support enabled\n");
			us->fflags |= US_FL_SANE_SENSE;

			/*
			 * Indicate to the user that we truncated their sense
			 * because we didn't know it supported larger sense.
			 */
			usb_stor_dbg(us, "-- Sense data truncated to %i from %i\n",
				     US_SENSE_SIZE,
				     srb->sense_buffer[7] + 8);
			srb->sense_buffer[7] = (US_SENSE_SIZE - 8);
		}

		scsi_normalize_sense(srb->sense_buffer, SCSI_SENSE_BUFFERSIZE,
				     &sshdr);

		usb_stor_dbg(us, "-- Result from auto-sense is %d\n",
			     temp_result);
		usb_stor_dbg(us, "-- code: 0x%x, key: 0x%x, ASC: 0x%x, ASCQ: 0x%x\n",
			     sshdr.response_code, sshdr.sense_key,
			     sshdr.asc, sshdr.ascq);
#ifdef CONFIG_USB_STORAGE_DEBUG
		usb_stor_show_sense(us, sshdr.sense_key, sshdr.asc, sshdr.ascq);
#endif

		/* set the result so the higher layers expect this data */
		srb->result = SAM_STAT_CHECK_CONDITION;

		scdd = scsi_sense_desc_find(srb->sense_buffer,
					    SCSI_SENSE_BUFFERSIZE, 4);
		fm_ili = (scdd ? scdd[3] : srb->sense_buffer[2]) & 0xA0;

		/*
		 * We often get empty sense data.  This could indicate that
		 * everything worked or that there was an unspecified
		 * problem.  We have to decide which.
		 */
		if (sshdr.sense_key == 0 && sshdr.asc == 0 && sshdr.ascq == 0 &&
		    fm_ili == 0) {
			/*
			 * If things are really okay, then let's show that.
			 * Zero out the sense buffer so the higher layers
			 * won't realize we did an unsolicited auto-sense.
			 */
			if (result == USB_STOR_TRANSPORT_GOOD) {
				srb->result = SAM_STAT_GOOD;
				srb->sense_buffer[0] = 0x0;
			}

			/*
			 * ATA-passthru commands use sense data to report
			 * the command completion status, and often devices
			 * return Check Condition status when nothing is
			 * wrong.
			 */
			else if (srb->cmnd[0] == ATA_16 ||
					srb->cmnd[0] == ATA_12) {
				/* leave the data alone */
			}

			/*
			 * If there was a problem, report an unspecified
			 * hardware error to prevent the higher layers from
			 * entering an infinite retry loop.
			 */
			else {
				srb->result = DID_ERROR << 16;
				if ((sshdr.response_code & 0x72) == 0x72)
					srb->sense_buffer[1] = HARDWARE_ERROR;
				else
					srb->sense_buffer[2] = HARDWARE_ERROR;
			}
		}
	}

	/*
	 * Some devices don't work or return incorrect data the first
	 * time they get a READ(10) command, or for the first READ(10)
	 * after a media change.  If the INITIAL_READ10 flag is set,
	 * keep track of whether READ(10) commands succeed.  If the
	 * previous one succeeded and this one failed, set the REDO_READ10
	 * flag to force a retry.
	 */
	if (unlikely((us->fflags & US_FL_INITIAL_READ10) &&
			srb->cmnd[0] == READ_10)) {
		if (srb->result == SAM_STAT_GOOD) {
			set_bit(US_FLIDX_READ10_WORKED, &us->dflags);
		} else if (test_bit(US_FLIDX_READ10_WORKED, &us->dflags)) {
			clear_bit(US_FLIDX_READ10_WORKED, &us->dflags);
			set_bit(US_FLIDX_REDO_READ10, &us->dflags);
		}

		/*
		 * Next, if the REDO_READ10 flag is set, return a result
		 * code that will cause the SCSI core to retry the READ(10)
		 * command immediately.
		 */
		if (test_bit(US_FLIDX_REDO_READ10, &us->dflags)) {
			clear_bit(US_FLIDX_REDO_READ10, &us->dflags);
			srb->result = DID_IMM_RETRY << 16;
			srb->sense_buffer[0] = 0;
		}
	}

	/* Did we transfer less than the minimum amount required? */
	if ((srb->result == SAM_STAT_GOOD || srb->sense_buffer[2] == 0) &&
			scsi_bufflen(srb) - scsi_get_resid(srb) < srb->underflow)
		srb->result = DID_ERROR << 16;

	last_sector_hacks(us, srb);
	return;

	/*
	 * Error and abort processing: try to resynchronize with the device
	 * by issuing a port reset.  If that fails, try a class-specific
	 * device reset.
	 */
  Handle_Errors:

	/*
	 * Set the RESETTING bit, and clear the ABORTING bit so that
	 * the reset may proceed.
	 */
	scsi_lock(us_to_host(us));
	set_bit(US_FLIDX_RESETTING, &us->dflags);
	clear_bit(US_FLIDX_ABORTING, &us->dflags);
	scsi_unlock(us_to_host(us));

	/*
	 * We must release the device lock because the pre_reset routine
	 * will want to acquire it.
	 */
	mutex_unlock(&us->dev_mutex);
	result = usb_stor_port_reset(us);
	mutex_lock(&us->dev_mutex);

	if (result < 0) {
		scsi_lock(us_to_host(us));
		usb_stor_report_device_reset(us);
		scsi_unlock(us_to_host(us));
		us->transport_reset(us);
	}
	clear_bit(US_FLIDX_RESETTING, &us->dflags);
	last_sector_hacks(us, srb);
}