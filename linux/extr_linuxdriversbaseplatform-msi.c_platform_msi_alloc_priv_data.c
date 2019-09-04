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
struct platform_msi_priv_data {scalar_t__ devid; struct device* dev; scalar_t__ write_msg; } ;
struct device {TYPE_1__* msi_domain; } ;
typedef  scalar_t__ irq_write_msi_msg_t ;
struct TYPE_2__ {scalar_t__ bus_token; } ;

/* Variables and functions */
 int DEV_ID_SHIFT ; 
 scalar_t__ DOMAIN_BUS_PLATFORM_MSI ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct platform_msi_priv_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MAX_DEV_MSIS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_to_msi_list (struct device*) ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct platform_msi_priv_data*) ; 
 struct platform_msi_priv_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_msi_devid_ida ; 

__attribute__((used)) static struct platform_msi_priv_data *
platform_msi_alloc_priv_data(struct device *dev, unsigned int nvec,
			     irq_write_msi_msg_t write_msi_msg)
{
	struct platform_msi_priv_data *datap;
	/*
	 * Limit the number of interrupts to 2048 per device. Should we
	 * need to bump this up, DEV_ID_SHIFT should be adjusted
	 * accordingly (which would impact the max number of MSI
	 * capable devices).
	 */
	if (!dev->msi_domain || !write_msi_msg || !nvec || nvec > MAX_DEV_MSIS)
		return ERR_PTR(-EINVAL);

	if (dev->msi_domain->bus_token != DOMAIN_BUS_PLATFORM_MSI) {
		dev_err(dev, "Incompatible msi_domain, giving up\n");
		return ERR_PTR(-EINVAL);
	}

	/* Already had a helping of MSI? Greed... */
	if (!list_empty(dev_to_msi_list(dev)))
		return ERR_PTR(-EBUSY);

	datap = kzalloc(sizeof(*datap), GFP_KERNEL);
	if (!datap)
		return ERR_PTR(-ENOMEM);

	datap->devid = ida_simple_get(&platform_msi_devid_ida,
				      0, 1 << DEV_ID_SHIFT, GFP_KERNEL);
	if (datap->devid < 0) {
		int err = datap->devid;
		kfree(datap);
		return ERR_PTR(err);
	}

	datap->write_msg = write_msi_msg;
	datap->dev = dev;

	return datap;
}