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
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  va; } ;
struct TYPE_3__ {int /*<<< orphan*/  va; } ;
struct mic_device {int /*<<< orphan*/  id; TYPE_2__ mmio; TYPE_1__ aper; int /*<<< orphan*/  cosm_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cosm_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mic_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mic_device*) ; 
 int /*<<< orphan*/  mic_delete_debug_dir (struct mic_device*) ; 
 int /*<<< orphan*/  mic_dp_uninit (struct mic_device*) ; 
 int /*<<< orphan*/  mic_free_interrupts (struct mic_device*,struct pci_dev*) ; 
 int /*<<< orphan*/  mic_smpt_uninit (struct mic_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct mic_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void mic_remove(struct pci_dev *pdev)
{
	struct mic_device *mdev;

	mdev = pci_get_drvdata(pdev);
	if (!mdev)
		return;

	cosm_unregister_device(mdev->cosm_dev);
	mic_delete_debug_dir(mdev);
	mic_dp_uninit(mdev);
	mic_smpt_uninit(mdev);
	mic_free_interrupts(mdev, pdev);
	iounmap(mdev->aper.va);
	iounmap(mdev->mmio.va);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	ida_simple_remove(&g_mic_ida, mdev->id);
	kfree(mdev);
}