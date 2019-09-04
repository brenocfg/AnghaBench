#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct msi_domain_info {struct its_node* data; } ;
struct its_node {int /*<<< orphan*/  dev_alloc_lock; } ;
struct its_device {int shared; } ;
struct irq_domain {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_9__ {TYPE_2__* scratchpad; } ;
typedef  TYPE_3__ msi_alloc_info_t ;
struct TYPE_11__ {int /*<<< orphan*/  has_direct_lpi; } ;
struct TYPE_10__ {TYPE_1__* dev; } ;
struct TYPE_8__ {scalar_t__ ul; struct its_device* ptr; } ;
struct TYPE_7__ {scalar_t__ device_id; struct its_node* its; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,scalar_t__) ; 
 TYPE_6__* gic_rdists ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 struct its_device* its_create_device (struct its_node*,scalar_t__,int,int) ; 
 struct its_device* its_find_device (struct its_node*,scalar_t__) ; 
 struct msi_domain_info* msi_get_domain_info (struct irq_domain*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 TYPE_4__ vpe_proxy ; 

__attribute__((used)) static int its_msi_prepare(struct irq_domain *domain, struct device *dev,
			   int nvec, msi_alloc_info_t *info)
{
	struct its_node *its;
	struct its_device *its_dev;
	struct msi_domain_info *msi_info;
	u32 dev_id;
	int err = 0;

	/*
	 * We ignore "dev" entierely, and rely on the dev_id that has
	 * been passed via the scratchpad. This limits this domain's
	 * usefulness to upper layers that definitely know that they
	 * are built on top of the ITS.
	 */
	dev_id = info->scratchpad[0].ul;

	msi_info = msi_get_domain_info(domain);
	its = msi_info->data;

	if (!gic_rdists->has_direct_lpi &&
	    vpe_proxy.dev &&
	    vpe_proxy.dev->its == its &&
	    dev_id == vpe_proxy.dev->device_id) {
		/* Bad luck. Get yourself a better implementation */
		WARN_ONCE(1, "DevId %x clashes with GICv4 VPE proxy device\n",
			  dev_id);
		return -EINVAL;
	}

	mutex_lock(&its->dev_alloc_lock);
	its_dev = its_find_device(its, dev_id);
	if (its_dev) {
		/*
		 * We already have seen this ID, probably through
		 * another alias (PCI bridge of some sort). No need to
		 * create the device.
		 */
		its_dev->shared = true;
		pr_debug("Reusing ITT for devID %x\n", dev_id);
		goto out;
	}

	its_dev = its_create_device(its, dev_id, nvec, true);
	if (!its_dev) {
		err = -ENOMEM;
		goto out;
	}

	pr_debug("ITT %d entries, %d bits\n", nvec, ilog2(nvec));
out:
	mutex_unlock(&its->dev_alloc_lock);
	info->scratchpad[0].ptr = its_dev;
	return err;
}