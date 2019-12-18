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
typedef  unsigned int u32 ;
struct vme_master_resource {int /*<<< orphan*/  lock; scalar_t__ kern_base; TYPE_1__* parent; } ;
struct device {int dummy; } ;
struct ca91cx42_driver {int /*<<< orphan*/  vme_rmw; scalar_t__ base; } ;
typedef  uintptr_t loff_t ;
struct TYPE_2__ {struct device* parent; struct ca91cx42_driver* driver_priv; } ;

/* Variables and functions */
 uintptr_t CA91CX42_SCYC_CTL_CYC_RMW ; 
 unsigned int EINVAL ; 
 scalar_t__ SCYC_ADDR ; 
 scalar_t__ SCYC_CMP ; 
 scalar_t__ SCYC_CTL ; 
 scalar_t__ SCYC_EN ; 
 scalar_t__ SCYC_SWP ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (uintptr_t,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int ca91cx42_master_rmw(struct vme_master_resource *image,
	unsigned int mask, unsigned int compare, unsigned int swap,
	loff_t offset)
{
	u32 result;
	uintptr_t pci_addr;
	struct ca91cx42_driver *bridge;
	struct device *dev;

	bridge = image->parent->driver_priv;
	dev = image->parent->parent;

	/* Find the PCI address that maps to the desired VME address */

	/* Locking as we can only do one of these at a time */
	mutex_lock(&bridge->vme_rmw);

	/* Lock image */
	spin_lock(&image->lock);

	pci_addr = (uintptr_t)image->kern_base + offset;

	/* Address must be 4-byte aligned */
	if (pci_addr & 0x3) {
		dev_err(dev, "RMW Address not 4-byte aligned\n");
		result = -EINVAL;
		goto out;
	}

	/* Ensure RMW Disabled whilst configuring */
	iowrite32(0, bridge->base + SCYC_CTL);

	/* Configure registers */
	iowrite32(mask, bridge->base + SCYC_EN);
	iowrite32(compare, bridge->base + SCYC_CMP);
	iowrite32(swap, bridge->base + SCYC_SWP);
	iowrite32(pci_addr, bridge->base + SCYC_ADDR);

	/* Enable RMW */
	iowrite32(CA91CX42_SCYC_CTL_CYC_RMW, bridge->base + SCYC_CTL);

	/* Kick process off with a read to the required address. */
	result = ioread32(image->kern_base + offset);

	/* Disable RMW */
	iowrite32(0, bridge->base + SCYC_CTL);

out:
	spin_unlock(&image->lock);

	mutex_unlock(&bridge->vme_rmw);

	return result;
}