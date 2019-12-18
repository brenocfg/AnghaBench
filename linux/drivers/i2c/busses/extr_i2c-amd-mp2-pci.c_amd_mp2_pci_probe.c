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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct amd_mp2_dev {int probed; struct pci_dev* pci_dev; int /*<<< orphan*/  c2p_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int amd_mp2_pci_init (struct amd_mp2_dev*,struct pci_dev*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct amd_mp2_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amd_mp2_pci_probe(struct pci_dev *pci_dev,
			     const struct pci_device_id *id)
{
	struct amd_mp2_dev *privdata;
	int rc;

	privdata = devm_kzalloc(&pci_dev->dev, sizeof(*privdata), GFP_KERNEL);
	if (!privdata)
		return -ENOMEM;

	rc = amd_mp2_pci_init(privdata, pci_dev);
	if (rc)
		return rc;

	mutex_init(&privdata->c2p_lock);
	privdata->pci_dev = pci_dev;

	pm_runtime_set_autosuspend_delay(&pci_dev->dev, 1000);
	pm_runtime_use_autosuspend(&pci_dev->dev);
	pm_runtime_put_autosuspend(&pci_dev->dev);
	pm_runtime_allow(&pci_dev->dev);

	privdata->probed = true;

	dev_info(&pci_dev->dev, "MP2 device registered.\n");
	return 0;
}