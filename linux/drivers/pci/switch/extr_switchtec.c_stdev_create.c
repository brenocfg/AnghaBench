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
struct device {int /*<<< orphan*/  devt; int /*<<< orphan*/  release; int /*<<< orphan*/  groups; int /*<<< orphan*/ * parent; int /*<<< orphan*/  class; } ;
struct cdev {int /*<<< orphan*/  owner; } ;
struct switchtec_dev {int alive; struct device dev; struct cdev cdev; int /*<<< orphan*/  event_cnt; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  link_event_work; int /*<<< orphan*/  mrpc_timeout; int /*<<< orphan*/  mrpc_work; scalar_t__ mrpc_busy; int /*<<< orphan*/  mrpc_mutex; int /*<<< orphan*/  mrpc_queue; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct switchtec_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_init (struct cdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct switchtec_dev* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_event_work ; 
 int /*<<< orphan*/  mrpc_event_work ; 
 int /*<<< orphan*/  mrpc_timeout_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  stdev_release ; 
 int /*<<< orphan*/  switchtec_class ; 
 int /*<<< orphan*/  switchtec_device_groups ; 
 int /*<<< orphan*/  switchtec_devt ; 
 int /*<<< orphan*/  switchtec_fops ; 
 int /*<<< orphan*/  switchtec_minor_ida ; 

__attribute__((used)) static struct switchtec_dev *stdev_create(struct pci_dev *pdev)
{
	struct switchtec_dev *stdev;
	int minor;
	struct device *dev;
	struct cdev *cdev;
	int rc;

	stdev = kzalloc_node(sizeof(*stdev), GFP_KERNEL,
			     dev_to_node(&pdev->dev));
	if (!stdev)
		return ERR_PTR(-ENOMEM);

	stdev->alive = true;
	stdev->pdev = pdev;
	INIT_LIST_HEAD(&stdev->mrpc_queue);
	mutex_init(&stdev->mrpc_mutex);
	stdev->mrpc_busy = 0;
	INIT_WORK(&stdev->mrpc_work, mrpc_event_work);
	INIT_DELAYED_WORK(&stdev->mrpc_timeout, mrpc_timeout_work);
	INIT_WORK(&stdev->link_event_work, link_event_work);
	init_waitqueue_head(&stdev->event_wq);
	atomic_set(&stdev->event_cnt, 0);

	dev = &stdev->dev;
	device_initialize(dev);
	dev->class = switchtec_class;
	dev->parent = &pdev->dev;
	dev->groups = switchtec_device_groups;
	dev->release = stdev_release;

	minor = ida_simple_get(&switchtec_minor_ida, 0, 0,
			       GFP_KERNEL);
	if (minor < 0) {
		rc = minor;
		goto err_put;
	}

	dev->devt = MKDEV(MAJOR(switchtec_devt), minor);
	dev_set_name(dev, "switchtec%d", minor);

	cdev = &stdev->cdev;
	cdev_init(cdev, &switchtec_fops);
	cdev->owner = THIS_MODULE;

	return stdev;

err_put:
	put_device(&stdev->dev);
	return ERR_PTR(rc);
}