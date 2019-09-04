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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ en; } ;
struct ngene {TYPE_1__ ci; int /*<<< orphan*/ * channel; int /*<<< orphan*/  event_tasklet; } ;

/* Variables and functions */
 int MAX_STREAM ; 
 int /*<<< orphan*/  cxd_detach (struct ngene*) ; 
 int /*<<< orphan*/  ngene_release_buffers (struct ngene*) ; 
 int /*<<< orphan*/  ngene_stop (struct ngene*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ngene* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void ngene_remove(struct pci_dev *pdev)
{
	struct ngene *dev = pci_get_drvdata(pdev);
	int i;

	tasklet_kill(&dev->event_tasklet);
	for (i = MAX_STREAM - 1; i >= 0; i--)
		release_channel(&dev->channel[i]);
	if (dev->ci.en)
		cxd_detach(dev);
	ngene_stop(dev);
	ngene_release_buffers(dev);
	pci_disable_device(pdev);
}