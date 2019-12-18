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
struct nci_dev {int dummy; } ;
struct fdp_nci_info {scalar_t__ ram_version; scalar_t__ ram_patch_version; int setup_patch_sent; int setup_reset_ntf; int setup_patch_ntf; int setup_patch_status; int /*<<< orphan*/  setup_wq; int /*<<< orphan*/  ndev; TYPE_2__* phy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* i2c_dev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FDP_FW_UPDATE_SLEEP ; 
 int /*<<< orphan*/  NCI_PATCH_TYPE_EOT ; 
 int /*<<< orphan*/  NCI_PATCH_TYPE_RAM ; 
 int fdp_nci_create_conn (struct nci_dev*) ; 
 int fdp_nci_patch_cmd (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int fdp_nci_send_patch (struct nci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int nci_core_conn_close (int /*<<< orphan*/ ,int) ; 
 struct fdp_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  nfc_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fdp_nci_patch_ram(struct nci_dev *ndev)
{
	struct fdp_nci_info *info = nci_get_drvdata(ndev);
	struct device *dev = &info->phy->i2c_dev->dev;
	int conn_id;
	int r = 0;

	if (info->ram_version >= info->ram_patch_version)
		goto out;

	info->setup_patch_sent = 0;
	info->setup_reset_ntf = 0;
	info->setup_patch_ntf = 0;

	/* Patch init request */
	r = fdp_nci_patch_cmd(ndev, NCI_PATCH_TYPE_RAM);
	if (r)
		goto out;

	/* Patch data connection creation */
	conn_id = fdp_nci_create_conn(ndev);
	if (conn_id < 0) {
		r = conn_id;
		goto out;
	}

	/* Send the patch over the data connection */
	r = fdp_nci_send_patch(ndev, conn_id, NCI_PATCH_TYPE_RAM);
	if (r)
		goto out;

	/* Wait for all the packets to be send over i2c */
	wait_event_interruptible(info->setup_wq,
				 info->setup_patch_sent == 1);

	/* make sure that the NFCC processed the last data packet */
	msleep(FDP_FW_UPDATE_SLEEP);

	/* Close the data connection */
	r = nci_core_conn_close(info->ndev, conn_id);
	if (r)
		goto out;

	/* Patch finish message */
	if (fdp_nci_patch_cmd(ndev, NCI_PATCH_TYPE_EOT)) {
		nfc_err(dev, "RAM patch error 0x%x\n", r);
		r = -EINVAL;
		goto out;
	}

	/* If the patch notification didn't arrive yet, wait for it */
	wait_event_interruptible(info->setup_wq, info->setup_patch_ntf);

	/* Check if the patching was successful */
	r = info->setup_patch_status;
	if (r) {
		nfc_err(dev, "RAM patch error 0x%x\n", r);
		r = -EINVAL;
		goto out;
	}

	/*
	 * We need to wait for the reset notification before we
	 * can continue
	 */
	wait_event_interruptible(info->setup_wq, info->setup_reset_ntf);

out:
	return r;
}