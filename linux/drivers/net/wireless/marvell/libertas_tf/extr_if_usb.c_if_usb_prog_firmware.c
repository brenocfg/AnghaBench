#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lbtf_private {scalar_t__ surpriseremoved; struct if_usb_card* card; } ;
struct if_usb_card {scalar_t__ bootcmdresp; int CRC_OK; int fwseqnum; struct lbtf_private* priv; TYPE_2__* fw; scalar_t__ fwdnldover; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  fw_timeout; int /*<<< orphan*/  fw_wq; scalar_t__ fwfinalblk; scalar_t__ totalbytes; scalar_t__ fwlastblksent; TYPE_1__* udev; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_CMD_FW_BY_USB ; 
 int /*<<< orphan*/  LBTF_DEB_USB ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ check_fwfile_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_usb_issue_boot_command (struct if_usb_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_usb_reset_device (struct lbtf_private*) ; 
 int /*<<< orphan*/  if_usb_send_fw_pkt (struct if_usb_card*) ; 
 int /*<<< orphan*/  if_usb_setup_firmware (struct lbtf_private*) ; 
 scalar_t__ if_usb_submit_rx_urb_fwload (struct if_usb_card*) ; 
 int /*<<< orphan*/  kernel_param_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_param_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbtf_deb_usbd (int /*<<< orphan*/ *,char*) ; 
 int lbtf_fw_name ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  release_firmware (TYPE_2__*) ; 
 int request_firmware (TYPE_2__**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int if_usb_prog_firmware(struct lbtf_private *priv)
{
	struct if_usb_card *cardp = priv->card;
	int i = 0;
	static int reset_count = 10;
	int ret = 0;

	lbtf_deb_enter(LBTF_DEB_USB);

	cardp->priv = priv;

	kernel_param_lock(THIS_MODULE);
	ret = request_firmware(&cardp->fw, lbtf_fw_name, &cardp->udev->dev);
	if (ret < 0) {
		pr_err("request_firmware() failed with %#x\n", ret);
		pr_err("firmware %s not found\n", lbtf_fw_name);
		kernel_param_unlock(THIS_MODULE);
		goto done;
	}
	kernel_param_unlock(THIS_MODULE);

	if (check_fwfile_format(cardp->fw->data, cardp->fw->size))
		goto release_fw;

restart:
	if (if_usb_submit_rx_urb_fwload(cardp) < 0) {
		lbtf_deb_usbd(&cardp->udev->dev, "URB submission is failed\n");
		ret = -1;
		goto release_fw;
	}

	cardp->bootcmdresp = 0;
	do {
		int j = 0;
		i++;
		/* Issue Boot command = 1, Boot from Download-FW */
		if_usb_issue_boot_command(cardp, BOOT_CMD_FW_BY_USB);
		/* wait for command response */
		do {
			j++;
			msleep_interruptible(100);
		} while (cardp->bootcmdresp == 0 && j < 10);
	} while (cardp->bootcmdresp == 0 && i < 5);

	if (cardp->bootcmdresp <= 0) {
		if (--reset_count >= 0) {
			if_usb_reset_device(priv);
			goto restart;
		}
		return -1;
	}

	i = 0;

	cardp->totalbytes = 0;
	cardp->fwlastblksent = 0;
	cardp->CRC_OK = 1;
	cardp->fwdnldover = 0;
	cardp->fwseqnum = -1;
	cardp->totalbytes = 0;
	cardp->fwfinalblk = 0;

	/* Send the first firmware packet... */
	if_usb_send_fw_pkt(cardp);

	/* ... and wait for the process to complete */
	wait_event_interruptible(cardp->fw_wq, cardp->priv->surpriseremoved ||
					       cardp->fwdnldover);

	del_timer_sync(&cardp->fw_timeout);
	usb_kill_urb(cardp->rx_urb);

	if (!cardp->fwdnldover) {
		pr_info("failed to load fw, resetting device!\n");
		if (--reset_count >= 0) {
			if_usb_reset_device(priv);
			goto restart;
		}

		pr_info("FW download failure, time = %d ms\n", i * 100);
		ret = -1;
		goto release_fw;
	}

 release_fw:
	release_firmware(cardp->fw);
	cardp->fw = NULL;

	if_usb_setup_firmware(cardp->priv);

 done:
	lbtf_deb_leave_args(LBTF_DEB_USB, "ret %d", ret);
	return ret;
}