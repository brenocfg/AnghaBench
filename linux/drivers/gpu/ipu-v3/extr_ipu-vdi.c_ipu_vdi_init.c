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
typedef  int /*<<< orphan*/  u32 ;
struct ipu_vdi {struct ipu_soc* ipu; int /*<<< orphan*/  base; int /*<<< orphan*/  module; int /*<<< orphan*/  lock; } ;
struct ipu_soc {struct ipu_vdi* vdi_priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,unsigned long,int /*<<< orphan*/ ) ; 
 struct ipu_vdi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ipu_vdi_init(struct ipu_soc *ipu, struct device *dev,
		 unsigned long base, u32 module)
{
	struct ipu_vdi *vdi;

	vdi = devm_kzalloc(dev, sizeof(*vdi), GFP_KERNEL);
	if (!vdi)
		return -ENOMEM;

	ipu->vdi_priv = vdi;

	spin_lock_init(&vdi->lock);
	vdi->module = module;
	vdi->base = devm_ioremap(dev, base, PAGE_SIZE);
	if (!vdi->base)
		return -ENOMEM;

	dev_dbg(dev, "VDI base: 0x%08lx remapped to %p\n", base, vdi->base);
	vdi->ipu = ipu;

	return 0;
}