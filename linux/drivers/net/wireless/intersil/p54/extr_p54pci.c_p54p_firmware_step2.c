#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct device* parent; } ;
struct pci_dev {TYPE_2__ dev; } ;
struct TYPE_5__ {struct ieee80211_hw* hw; } ;
struct p54p_priv {int /*<<< orphan*/  fw_loaded; struct firmware const* firmware; struct pci_dev* pdev; TYPE_1__ common; } ;
struct ieee80211_hw {int dummy; } ;
struct firmware {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_release_driver (TYPE_2__*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int p54_read_eeprom (struct ieee80211_hw*) ; 
 int p54_register_common (struct ieee80211_hw*,TYPE_2__*) ; 
 int p54p_open (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  p54p_stop (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 

__attribute__((used)) static void p54p_firmware_step2(const struct firmware *fw,
				void *context)
{
	struct p54p_priv *priv = context;
	struct ieee80211_hw *dev = priv->common.hw;
	struct pci_dev *pdev = priv->pdev;
	int err;

	if (!fw) {
		dev_err(&pdev->dev, "Cannot find firmware (isl3886pci)\n");
		err = -ENOENT;
		goto out;
	}

	priv->firmware = fw;

	err = p54p_open(dev);
	if (err)
		goto out;
	err = p54_read_eeprom(dev);
	p54p_stop(dev);
	if (err)
		goto out;

	err = p54_register_common(dev, &pdev->dev);
	if (err)
		goto out;

out:

	complete(&priv->fw_loaded);

	if (err) {
		struct device *parent = pdev->dev.parent;

		if (parent)
			device_lock(parent);

		/*
		 * This will indirectly result in a call to p54p_remove.
		 * Hence, we don't need to bother with freeing any
		 * allocated ressources at all.
		 */
		device_release_driver(&pdev->dev);

		if (parent)
			device_unlock(parent);
	}

	pci_dev_put(pdev);
}