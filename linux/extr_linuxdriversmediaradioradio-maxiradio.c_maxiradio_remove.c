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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct maxiradio {int /*<<< orphan*/  io; int /*<<< orphan*/  tea; } ;

/* Variables and functions */
 struct v4l2_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct maxiradio*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_tea575x_exit (int /*<<< orphan*/ *) ; 
 struct maxiradio* to_maxiradio (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (struct v4l2_device*) ; 

__attribute__((used)) static void maxiradio_remove(struct pci_dev *pdev)
{
	struct v4l2_device *v4l2_dev = dev_get_drvdata(&pdev->dev);
	struct maxiradio *dev = to_maxiradio(v4l2_dev);

	snd_tea575x_exit(&dev->tea);
	/* Turn off power */
	outb(0, dev->io);
	v4l2_device_unregister(v4l2_dev);
	release_region(pci_resource_start(pdev, 0), pci_resource_len(pdev, 0));
	kfree(dev);
}