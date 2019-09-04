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
struct ipu_soc {struct ipu_cpmem* cpmem_priv; } ;
struct ipu_cpmem {struct ipu_soc* ipu; int /*<<< orphan*/  base; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SZ_128K ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,unsigned long,int /*<<< orphan*/ ) ; 
 struct ipu_cpmem* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ipu_cpmem_init(struct ipu_soc *ipu, struct device *dev, unsigned long base)
{
	struct ipu_cpmem *cpmem;

	cpmem = devm_kzalloc(dev, sizeof(*cpmem), GFP_KERNEL);
	if (!cpmem)
		return -ENOMEM;

	ipu->cpmem_priv = cpmem;

	spin_lock_init(&cpmem->lock);
	cpmem->base = devm_ioremap(dev, base, SZ_128K);
	if (!cpmem->base)
		return -ENOMEM;

	dev_dbg(dev, "CPMEM base: 0x%08lx remapped to %p\n",
		base, cpmem->base);
	cpmem->ipu = ipu;

	return 0;
}