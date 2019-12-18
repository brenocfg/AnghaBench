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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mpeg; } ;
struct cx88_core {struct cx8802_dev* dvbdev; TYPE_1__ board; } ;
struct cx8802_dev {int /*<<< orphan*/  devlist; int /*<<< orphan*/  drvlist; struct cx88_core* core; struct pci_dev* pci; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx8802_devlist ; 
 int cx8802_init_common (struct cx8802_dev*) ; 
 int /*<<< orphan*/  cx8802_mutex ; 
 struct cx88_core* cx88_core_get (struct pci_dev*) ; 
 int /*<<< orphan*/  cx88_core_put (struct cx88_core*,struct pci_dev*) ; 
 int /*<<< orphan*/  kfree (struct cx8802_dev*) ; 
 struct cx8802_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  request_modules (struct cx8802_dev*) ; 

__attribute__((used)) static int cx8802_probe(struct pci_dev *pci_dev,
			const struct pci_device_id *pci_id)
{
	struct cx8802_dev *dev;
	struct cx88_core  *core;
	int err;

	/* general setup */
	core = cx88_core_get(pci_dev);
	if (!core)
		return -EINVAL;

	pr_info("cx2388x 8802 Driver Manager\n");

	err = -ENODEV;
	if (!core->board.mpeg)
		goto fail_core;

	err = -ENOMEM;
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		goto fail_core;
	dev->pci = pci_dev;
	dev->core = core;

	/* Maintain a reference so cx88-video can query the 8802 device. */
	core->dvbdev = dev;

	err = cx8802_init_common(dev);
	if (err != 0)
		goto fail_dev;

	INIT_LIST_HEAD(&dev->drvlist);
	mutex_lock(&cx8802_mutex);
	list_add_tail(&dev->devlist, &cx8802_devlist);
	mutex_unlock(&cx8802_mutex);

	/* now autoload cx88-dvb or cx88-blackbird */
	request_modules(dev);
	return 0;

 fail_dev:
	kfree(dev);
 fail_core:
	core->dvbdev = NULL;
	cx88_core_put(core, pci_dev);
	return err;
}