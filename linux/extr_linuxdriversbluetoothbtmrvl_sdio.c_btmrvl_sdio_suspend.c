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
struct sdio_func {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct btmrvl_sdio_card {TYPE_2__* plt_wake_cfg; struct btmrvl_private* priv; } ;
struct TYPE_4__ {struct hci_dev* hcidev; } ;
struct btmrvl_private {TYPE_3__* adapter; TYPE_1__ btmrvl_dev; } ;
typedef  int mmc_pm_flag_t ;
struct TYPE_6__ {int is_suspending; scalar_t__ hs_state; int is_suspended; } ;
struct TYPE_5__ {scalar_t__ irq_bt; int wake_by_bt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int EBUSY ; 
 int ENOSYS ; 
 scalar_t__ HS_ACTIVATED ; 
 int MMC_PM_KEEP_POWER ; 
 scalar_t__ btmrvl_enable_hs (struct btmrvl_private*) ; 
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  disable_irq_wake (scalar_t__) ; 
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 int /*<<< orphan*/  enable_irq_wake (scalar_t__) ; 
 int /*<<< orphan*/  hci_suspend_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  sdio_func_id (struct sdio_func*) ; 
 struct btmrvl_sdio_card* sdio_get_drvdata (struct sdio_func*) ; 
 int sdio_get_host_pm_caps (struct sdio_func*) ; 
 int sdio_set_host_pm_flags (struct sdio_func*,int) ; 

__attribute__((used)) static int btmrvl_sdio_suspend(struct device *dev)
{
	struct sdio_func *func = dev_to_sdio_func(dev);
	struct btmrvl_sdio_card *card;
	struct btmrvl_private *priv;
	mmc_pm_flag_t pm_flags;
	struct hci_dev *hcidev;

	if (func) {
		pm_flags = sdio_get_host_pm_caps(func);
		BT_DBG("%s: suspend: PM flags = 0x%x", sdio_func_id(func),
		       pm_flags);
		if (!(pm_flags & MMC_PM_KEEP_POWER)) {
			BT_ERR("%s: cannot remain alive while suspended",
			       sdio_func_id(func));
			return -ENOSYS;
		}
		card = sdio_get_drvdata(func);
		if (!card || !card->priv) {
			BT_ERR("card or priv structure is not valid");
			return 0;
		}
	} else {
		BT_ERR("sdio_func is not specified");
		return 0;
	}

	/* Enable platform specific wakeup interrupt */
	if (card->plt_wake_cfg && card->plt_wake_cfg->irq_bt >= 0) {
		card->plt_wake_cfg->wake_by_bt = false;
		enable_irq(card->plt_wake_cfg->irq_bt);
		enable_irq_wake(card->plt_wake_cfg->irq_bt);
	}

	priv = card->priv;
	priv->adapter->is_suspending = true;
	hcidev = priv->btmrvl_dev.hcidev;
	BT_DBG("%s: SDIO suspend", hcidev->name);
	hci_suspend_dev(hcidev);

	if (priv->adapter->hs_state != HS_ACTIVATED) {
		if (btmrvl_enable_hs(priv)) {
			BT_ERR("HS not activated, suspend failed!");
			/* Disable platform specific wakeup interrupt */
			if (card->plt_wake_cfg &&
			    card->plt_wake_cfg->irq_bt >= 0) {
				disable_irq_wake(card->plt_wake_cfg->irq_bt);
				disable_irq(card->plt_wake_cfg->irq_bt);
			}

			priv->adapter->is_suspending = false;
			return -EBUSY;
		}
	}

	priv->adapter->is_suspending = false;
	priv->adapter->is_suspended = true;

	/* We will keep the power when hs enabled successfully */
	if (priv->adapter->hs_state == HS_ACTIVATED) {
		BT_DBG("suspend with MMC_PM_KEEP_POWER");
		return sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
	}

	BT_DBG("suspend without MMC_PM_KEEP_POWER");
	return 0;
}