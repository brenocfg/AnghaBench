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
struct us_data {int dummy; } ;
struct scsi_cmnd {int cmd_len; int* cmnd; } ;

/* Variables and functions */
#define  INQUIRY 130 
#define  MODE_SENSE_10 129 
#define  REQUEST_SENSE 128 
 int /*<<< orphan*/  usb_stor_invoke_transport (struct scsi_cmnd*,struct us_data*) ; 

void usb_stor_ufi_command(struct scsi_cmnd *srb, struct us_data *us)
{
	/*
	 * fix some commands -- this is a form of mode translation
	 * UFI devices only accept 12 byte long commands
	 *
	 * NOTE: This only works because a scsi_cmnd struct field contains
	 * a unsigned char cmnd[16], so we know we have storage available
	 */

	/* Pad the ATAPI command with zeros */
	for (; srb->cmd_len < 12; srb->cmd_len++)
		srb->cmnd[srb->cmd_len] = 0;

	/* set command length to 12 bytes (this affects the transport layer) */
	srb->cmd_len = 12;

	/* XXX We should be constantly re-evaluating the need for these */

	/* determine the correct data length for these commands */
	switch (srb->cmnd[0]) {

		/* for INQUIRY, UFI devices only ever return 36 bytes */
	case INQUIRY:
		srb->cmnd[4] = 36;
		break;

		/* again, for MODE_SENSE_10, we get the minimum (8) */
	case MODE_SENSE_10:
		srb->cmnd[7] = 0;
		srb->cmnd[8] = 8;
		break;

		/* for REQUEST_SENSE, UFI devices only ever return 18 bytes */
	case REQUEST_SENSE:
		srb->cmnd[4] = 18;
		break;
	} /* end switch on cmnd[0] */

	/* send the command to the transport layer */
	usb_stor_invoke_transport(srb, us);
}