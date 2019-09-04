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
struct gspca_dev {char* usb_buf; int usb_err; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int EIO ; 
 int /*<<< orphan*/  configure_encrypted (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,...) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,char*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ val_reply (struct gspca_dev*,char*,int) ; 

__attribute__((used)) static int configure(struct gspca_dev *gspca_dev)
{
	int rc;
	char *buff = gspca_dev->usb_buf;

	gspca_dbg(gspca_dev, D_STREAM, "configure()\n\n");

	/*
	 * First driver sets a sort of encryption key
	 * A number of futur requests of this type have wValue and wIndex
	 * encrypted as follows:
	 * -Compute key = this wValue rotate left by 4 bits
	 *	(decrypt.py rotates right because we are decrypting)
	 * -Later packets encrypt packets by XOR'ing with key
	 *	XOR encrypt/decrypt is symmetrical
	 *	wValue, and wIndex are encrypted
	 *	bRequest is not and bRequestType is always 0xC0
	 *		This allows resyncing if key is unknown?
	 * By setting 0 we XOR with 0 and the shifting and XOR drops out
	 */
	rc = usb_control_msg(gspca_dev->dev, usb_rcvctrlpipe(gspca_dev->dev, 0),
			     0x16, 0xC0, 0x0000, 0x0000, buff, 2, 500);
	if (val_reply(gspca_dev, buff, rc)) {
		gspca_err(gspca_dev, "failed key req\n");
		return -EIO;
	}

	/*
	 * Next does some sort of 2 packet challenge / response
	 * evidence suggests its an Atmel I2C crypto part but nobody cares to
	 * look
	 * (to make sure its not cloned hardware?)
	 * Ignore: I want to work with their hardware, not clone it
	 * 16 bytes out challenge, requestType: 0x40
	 * 16 bytes in response, requestType: 0xC0
	 */

	rc = usb_control_msg(gspca_dev->dev, usb_sndctrlpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0001, 0x000F, NULL, 0, 500);
	if (rc < 0) {
		gspca_err(gspca_dev, "failed to replay packet 176 w/ rc %d\n",
			  rc);
		return rc;
	}

	rc = usb_control_msg(gspca_dev->dev, usb_sndctrlpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0000, 0x000F, NULL, 0, 500);
	if (rc < 0) {
		gspca_err(gspca_dev, "failed to replay packet 178 w/ rc %d\n",
			  rc);
		return rc;
	}

	rc = usb_control_msg(gspca_dev->dev, usb_sndctrlpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0001, 0x000F, NULL, 0, 500);
	if (rc < 0) {
		gspca_err(gspca_dev, "failed to replay packet 180 w/ rc %d\n",
			  rc);
		return rc;
	}

	/*
	 * Serial number?  Doesn't seem to be required
	 * cam1: \xE6\x0D\x00\x00, cam2: \x70\x19\x00\x00
	 * rc = usb_control_msg(gspca_dev->dev,
	 *			usb_rcvctrlpipe(gspca_dev->dev, 0),
	 *			0x20, 0xC0, 0x0000, 0x0000, buff, 4, 500);
	 */

	/* Large (EEPROM?) read, skip it since no idea what to do with it */
	gspca_dev->usb_err = 0;
	configure_encrypted(gspca_dev);
	if (gspca_dev->usb_err)
		return gspca_dev->usb_err;

	/* Omitted this by accident, does not work without it */
	rc = usb_control_msg(gspca_dev->dev, usb_sndctrlpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0003, 0x000F, NULL, 0, 500);
	if (rc < 0) {
		gspca_err(gspca_dev, "failed to replay final packet w/ rc %d\n",
			  rc);
		return rc;
	}

	gspca_dbg(gspca_dev, D_STREAM, "Configure complete\n\n");
	return 0;
}