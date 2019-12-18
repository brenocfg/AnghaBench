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
struct usnic_uiom_pd {int /*<<< orphan*/  domain; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_cnt; int /*<<< orphan*/  devs; } ;
struct usnic_uiom_dev {int /*<<< orphan*/  link; struct device* dev; } ;
struct device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IOMMU_CAP_CACHE_COHERENCY ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int iommu_attach_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  iommu_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_detach_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  kfree (struct usnic_uiom_dev*) ; 
 struct usnic_uiom_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_err (char*,int /*<<< orphan*/ ) ; 

int usnic_uiom_attach_dev_to_pd(struct usnic_uiom_pd *pd, struct device *dev)
{
	struct usnic_uiom_dev *uiom_dev;
	int err;

	uiom_dev = kzalloc(sizeof(*uiom_dev), GFP_ATOMIC);
	if (!uiom_dev)
		return -ENOMEM;
	uiom_dev->dev = dev;

	err = iommu_attach_device(pd->domain, dev);
	if (err)
		goto out_free_dev;

	if (!iommu_capable(dev->bus, IOMMU_CAP_CACHE_COHERENCY)) {
		usnic_err("IOMMU of %s does not support cache coherency\n",
				dev_name(dev));
		err = -EINVAL;
		goto out_detach_device;
	}

	spin_lock(&pd->lock);
	list_add_tail(&uiom_dev->link, &pd->devs);
	pd->dev_cnt++;
	spin_unlock(&pd->lock);

	return 0;

out_detach_device:
	iommu_detach_device(pd->domain, dev);
out_free_dev:
	kfree(uiom_dev);
	return err;
}