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
struct ipu_soc {struct ipu_ic_priv* ic_priv; } ;
struct ipu_ic_priv {TYPE_1__* task; struct ipu_soc* ipu; void* base; void* tpmem_base; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int task; int /*<<< orphan*/ * bit; int /*<<< orphan*/ * reg; struct ipu_ic_priv* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IC_NUM_TASKS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SZ_64K ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long,void*) ; 
 void* devm_ioremap (struct device*,unsigned long,int /*<<< orphan*/ ) ; 
 struct ipu_ic_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ic_task_bit ; 
 int /*<<< orphan*/ * ic_task_reg ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ipu_ic_init(struct ipu_soc *ipu, struct device *dev,
		unsigned long base, unsigned long tpmem_base)
{
	struct ipu_ic_priv *priv;
	int i;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ipu->ic_priv = priv;

	spin_lock_init(&priv->lock);
	priv->base = devm_ioremap(dev, base, PAGE_SIZE);
	if (!priv->base)
		return -ENOMEM;
	priv->tpmem_base = devm_ioremap(dev, tpmem_base, SZ_64K);
	if (!priv->tpmem_base)
		return -ENOMEM;

	dev_dbg(dev, "IC base: 0x%08lx remapped to %p\n", base, priv->base);

	priv->ipu = ipu;

	for (i = 0; i < IC_NUM_TASKS; i++) {
		priv->task[i].task = i;
		priv->task[i].priv = priv;
		priv->task[i].reg = &ic_task_reg[i];
		priv->task[i].bit = &ic_task_bit[i];
	}

	return 0;
}