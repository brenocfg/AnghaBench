#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct vme_master_resource {int number; int /*<<< orphan*/  lock; TYPE_1__* parent; } ;
struct fake_driver {TYPE_2__* masters; } ;
typedef  unsigned int loff_t ;
struct TYPE_4__ {unsigned int vme_base; unsigned int aspace; unsigned int cycle; } ;
struct TYPE_3__ {struct fake_driver* driver_priv; } ;

/* Variables and functions */
 unsigned int fake_vmeread32 (struct fake_driver*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fake_vmewrite32 (struct fake_driver*,unsigned int*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int fake_master_rmw(struct vme_master_resource *image,
		unsigned int mask, unsigned int compare, unsigned int swap,
		loff_t offset)
{
	u32 tmp, base;
	u32 aspace, cycle;
	int i;
	struct fake_driver *bridge;

	bridge = image->parent->driver_priv;

	/* Find the PCI address that maps to the desired VME address */
	i = image->number;

	base = bridge->masters[i].vme_base;
	aspace = bridge->masters[i].aspace;
	cycle = bridge->masters[i].cycle;

	/* Lock image */
	spin_lock(&image->lock);

	/* Read existing value */
	tmp = fake_vmeread32(bridge, base + offset, aspace, cycle);

	/* Perform check */
	if ((tmp && mask) == (compare && mask)) {
		tmp = tmp | (mask | swap);
		tmp = tmp & (~mask | swap);

		/* Write back */
		fake_vmewrite32(bridge, &tmp, base + offset, aspace, cycle);
	}

	/* Unlock image */
	spin_unlock(&image->lock);

	return tmp;
}