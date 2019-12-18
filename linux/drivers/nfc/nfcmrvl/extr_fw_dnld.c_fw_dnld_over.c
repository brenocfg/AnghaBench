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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  timer; int /*<<< orphan*/ * binary_config; int /*<<< orphan*/ * header; int /*<<< orphan*/ * fw; } ;
struct nfcmrvl_private {TYPE_2__ fw_dnld; TYPE_1__* ndev; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  nfc_dev; int /*<<< orphan*/  cmd_timer; int /*<<< orphan*/  cmd_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_fw_download_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nfc_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  nfcmrvl_chip_halt (struct nfcmrvl_private*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fw_dnld_over(struct nfcmrvl_private *priv, u32 error)
{
	if (priv->fw_dnld.fw) {
		release_firmware(priv->fw_dnld.fw);
		priv->fw_dnld.fw = NULL;
		priv->fw_dnld.header = NULL;
		priv->fw_dnld.binary_config = NULL;
	}

	atomic_set(&priv->ndev->cmd_cnt, 0);

	if (timer_pending(&priv->ndev->cmd_timer))
		del_timer_sync(&priv->ndev->cmd_timer);

	if (timer_pending(&priv->fw_dnld.timer))
		del_timer_sync(&priv->fw_dnld.timer);

	nfc_info(priv->dev, "FW loading over (%d)]\n", error);

	if (error != 0) {
		/* failed, halt the chip to avoid power consumption */
		nfcmrvl_chip_halt(priv);
	}

	nfc_fw_download_done(priv->ndev->nfc_dev, priv->fw_dnld.name, error);
}