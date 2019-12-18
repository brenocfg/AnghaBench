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
struct pci_dev {int dummy; } ;
struct cio2_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  media_dev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  cio2_fbpt_exit_dummy (struct cio2_device*) ; 
 int /*<<< orphan*/  cio2_queues_exit (struct cio2_device*) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct cio2_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cio2_pci_remove(struct pci_dev *pci_dev)
{
	struct cio2_device *cio2 = pci_get_drvdata(pci_dev);

	media_device_unregister(&cio2->media_dev);
	v4l2_async_notifier_unregister(&cio2->notifier);
	v4l2_async_notifier_cleanup(&cio2->notifier);
	cio2_queues_exit(cio2);
	cio2_fbpt_exit_dummy(cio2);
	v4l2_device_unregister(&cio2->v4l2_dev);
	media_device_cleanup(&cio2->media_dev);
	mutex_destroy(&cio2->lock);
}