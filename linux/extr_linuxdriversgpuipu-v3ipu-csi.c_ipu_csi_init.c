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
struct ipu_soc {struct ipu_csi** csi_priv; } ;
struct ipu_csi {int id; struct ipu_soc* ipu; int /*<<< orphan*/  base; struct clk* clk_ipu; int /*<<< orphan*/  module; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,unsigned long,int /*<<< orphan*/ ) ; 
 struct ipu_csi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ipu_csi_init(struct ipu_soc *ipu, struct device *dev, int id,
		 unsigned long base, u32 module, struct clk *clk_ipu)
{
	struct ipu_csi *csi;

	if (id > 1)
		return -ENODEV;

	csi = devm_kzalloc(dev, sizeof(*csi), GFP_KERNEL);
	if (!csi)
		return -ENOMEM;

	ipu->csi_priv[id] = csi;

	spin_lock_init(&csi->lock);
	csi->module = module;
	csi->id = id;
	csi->clk_ipu = clk_ipu;
	csi->base = devm_ioremap(dev, base, PAGE_SIZE);
	if (!csi->base)
		return -ENOMEM;

	dev_dbg(dev, "CSI%d base: 0x%08lx remapped to %p\n",
		id, base, csi->base);
	csi->ipu = ipu;

	return 0;
}