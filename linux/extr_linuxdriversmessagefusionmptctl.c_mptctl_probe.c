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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  done; int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_1__ ioctl_cmds; } ;
typedef  TYPE_2__ MPT_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static int
mptctl_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	MPT_ADAPTER *ioc = pci_get_drvdata(pdev);

	mutex_init(&ioc->ioctl_cmds.mutex);
	init_completion(&ioc->ioctl_cmds.done);
	return 0;
}