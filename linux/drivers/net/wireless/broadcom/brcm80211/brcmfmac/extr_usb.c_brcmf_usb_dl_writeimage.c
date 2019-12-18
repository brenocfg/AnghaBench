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
typedef  char u8 ;
typedef  scalar_t__ u32 ;
struct rdl_state_le {int /*<<< orphan*/  bytes; int /*<<< orphan*/  state; } ;
struct brcmf_usbdev_info {int dummy; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 scalar_t__ DL_BAD_CRC ; 
 scalar_t__ DL_BAD_HDR ; 
 int /*<<< orphan*/  DL_GETSTATE ; 
 int /*<<< orphan*/  DL_START ; 
 scalar_t__ DL_WAITING ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int TRX_RDL_CHUNK ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (char*,...) ; 
 int brcmf_usb_dl_cmd (struct brcmf_usbdev_info*,int /*<<< orphan*/ ,struct rdl_state_le*,int) ; 
 scalar_t__ brcmf_usb_dl_send_bulk (struct brcmf_usbdev_info*,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 

__attribute__((used)) static int
brcmf_usb_dl_writeimage(struct brcmf_usbdev_info *devinfo, u8 *fw, int fwlen)
{
	unsigned int sendlen, sent, dllen;
	char *bulkchunk = NULL, *dlpos;
	struct rdl_state_le state;
	u32 rdlstate, rdlbytes;
	int err = 0;

	brcmf_dbg(USB, "Enter, fw %p, len %d\n", fw, fwlen);

	bulkchunk = kmalloc(TRX_RDL_CHUNK, GFP_ATOMIC);
	if (bulkchunk == NULL) {
		err = -ENOMEM;
		goto fail;
	}

	/* 1) Prepare USB boot loader for runtime image */
	brcmf_usb_dl_cmd(devinfo, DL_START, &state, sizeof(state));

	rdlstate = le32_to_cpu(state.state);
	rdlbytes = le32_to_cpu(state.bytes);

	/* 2) Check we are in the Waiting state */
	if (rdlstate != DL_WAITING) {
		brcmf_err("Failed to DL_START\n");
		err = -EINVAL;
		goto fail;
	}
	sent = 0;
	dlpos = fw;
	dllen = fwlen;

	/* Get chip id and rev */
	while (rdlbytes != dllen) {
		/* Wait until the usb device reports it received all
		 * the bytes we sent */
		if ((rdlbytes == sent) && (rdlbytes != dllen)) {
			if ((dllen-sent) < TRX_RDL_CHUNK)
				sendlen = dllen-sent;
			else
				sendlen = TRX_RDL_CHUNK;

			/* simply avoid having to send a ZLP by ensuring we
			 * never have an even
			 * multiple of 64
			 */
			if (!(sendlen % 64))
				sendlen -= 4;

			/* send data */
			memcpy(bulkchunk, dlpos, sendlen);
			if (brcmf_usb_dl_send_bulk(devinfo, bulkchunk,
						   sendlen)) {
				brcmf_err("send_bulk failed\n");
				err = -EINVAL;
				goto fail;
			}

			dlpos += sendlen;
			sent += sendlen;
		}
		err = brcmf_usb_dl_cmd(devinfo, DL_GETSTATE, &state,
				       sizeof(state));
		if (err) {
			brcmf_err("DL_GETSTATE Failed\n");
			goto fail;
		}

		rdlstate = le32_to_cpu(state.state);
		rdlbytes = le32_to_cpu(state.bytes);

		/* restart if an error is reported */
		if (rdlstate == DL_BAD_HDR || rdlstate == DL_BAD_CRC) {
			brcmf_err("Bad Hdr or Bad CRC state %d\n",
				  rdlstate);
			err = -EINVAL;
			goto fail;
		}
	}

fail:
	kfree(bulkchunk);
	brcmf_dbg(USB, "Exit, err=%d\n", err);
	return err;
}