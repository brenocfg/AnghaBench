#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  revision; } ;
struct TYPE_2__ {scalar_t__ next_avail_src; } ;
struct mic_device {TYPE_1__ irq_info; int /*<<< orphan*/  mic_mutex; int /*<<< orphan*/  stepping; int /*<<< orphan*/  family; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mic_get_family (struct pci_dev*) ; 
 int /*<<< orphan*/  mic_ops_init (struct mic_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mic_device_init(struct mic_device *mdev, struct pci_dev *pdev)
{
	mdev->pdev = pdev;
	mdev->family = mic_get_family(pdev);
	mdev->stepping = pdev->revision;
	mic_ops_init(mdev);
	mutex_init(&mdev->mic_mutex);
	mdev->irq_info.next_avail_src = 0;
}