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
struct v4l2_device {int dummy; } ;
struct pci_dev {scalar_t__ irq; } ;
struct cx25821_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25821_dev_unregister (struct cx25821_dev*) ; 
 int /*<<< orphan*/  cx25821_shutdown (struct cx25821_dev*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct cx25821_dev*) ; 
 struct cx25821_dev* get_cx25821 (struct v4l2_device*) ; 
 int /*<<< orphan*/  kfree (struct cx25821_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct v4l2_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (struct v4l2_device*) ; 

__attribute__((used)) static void cx25821_finidev(struct pci_dev *pci_dev)
{
	struct v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	struct cx25821_dev *dev = get_cx25821(v4l2_dev);

	cx25821_shutdown(dev);
	pci_disable_device(pci_dev);

	/* unregister stuff */
	if (pci_dev->irq)
		free_irq(pci_dev->irq, dev);

	cx25821_dev_unregister(dev);
	v4l2_device_unregister(v4l2_dev);
	kfree(dev);
}