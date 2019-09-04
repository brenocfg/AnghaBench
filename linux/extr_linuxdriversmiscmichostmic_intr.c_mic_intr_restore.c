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
struct TYPE_4__ {int num_vectors; int* mic_msi_map; } ;
struct mic_device {TYPE_1__* intr_ops; TYPE_2__ irq_info; struct pci_dev* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* program_msi_to_src_map ) (struct mic_device*,int,int,int) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int MIC_NUM_OFFSETS ; 
 int /*<<< orphan*/  pci_dev_msi_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct mic_device*,int,int,int) ; 

void mic_intr_restore(struct mic_device *mdev)
{
	int entry, offset;
	struct pci_dev *pdev = mdev->pdev;

	if (!pci_dev_msi_enabled(pdev))
		return;

	for (entry = 0; entry < mdev->irq_info.num_vectors; entry++) {
		for (offset = 0; offset < MIC_NUM_OFFSETS; offset++) {
			if (mdev->irq_info.mic_msi_map[entry] & BIT(offset))
				mdev->intr_ops->program_msi_to_src_map(mdev,
					entry, offset, true);
		}
	}
}