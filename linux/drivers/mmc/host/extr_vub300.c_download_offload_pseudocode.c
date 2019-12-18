#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vub300_mmc_host {int /*<<< orphan*/  vub_name; TYPE_3__* udev; TYPE_1__* mmc; } ;
struct sdio_func {int vendor; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int vendor; int /*<<< orphan*/  device; } ;
struct mmc_card {int sdio_funcs; int /*<<< orphan*/  dev; struct sdio_func** sdio_func; TYPE_2__ cis; } ;
struct firmware {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct mmc_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  __download_offload_pseudocode (struct vub300_mmc_host*,struct firmware const*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void download_offload_pseudocode(struct vub300_mmc_host *vub300)
{
	struct mmc_card *card = vub300->mmc->card;
	int sdio_funcs = card->sdio_funcs;
	const struct firmware *fw = NULL;
	int l = snprintf(vub300->vub_name, sizeof(vub300->vub_name),
			 "vub_%04X%04X", card->cis.vendor, card->cis.device);
	int n = 0;
	int retval;
	for (n = 0; n < sdio_funcs; n++) {
		struct sdio_func *sf = card->sdio_func[n];
		l += snprintf(vub300->vub_name + l,
			      sizeof(vub300->vub_name) - l, "_%04X%04X",
			      sf->vendor, sf->device);
	}
	snprintf(vub300->vub_name + l, sizeof(vub300->vub_name) - l, ".bin");
	dev_info(&vub300->udev->dev, "requesting offload firmware %s\n",
		 vub300->vub_name);
	retval = request_firmware(&fw, vub300->vub_name, &card->dev);
	if (retval < 0) {
		strncpy(vub300->vub_name, "vub_default.bin",
			sizeof(vub300->vub_name));
		retval = request_firmware(&fw, vub300->vub_name, &card->dev);
		if (retval < 0) {
			strncpy(vub300->vub_name,
				"no SDIO offload firmware found",
				sizeof(vub300->vub_name));
		} else {
			__download_offload_pseudocode(vub300, fw);
			release_firmware(fw);
		}
	} else {
		__download_offload_pseudocode(vub300, fw);
		release_firmware(fw);
	}
}