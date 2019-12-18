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
struct ipu_soc {struct ipu_di** di_priv; } ;
struct ipu_di {int id; int inuse; struct ipu_soc* ipu; int /*<<< orphan*/  base; struct clk* clk_ipu; int /*<<< orphan*/  module; int /*<<< orphan*/  clk_di; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DI_BS_CLKGEN0 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,unsigned long,int /*<<< orphan*/ ) ; 
 struct ipu_di* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_write (struct ipu_di*,int,int /*<<< orphan*/ ) ; 

int ipu_di_init(struct ipu_soc *ipu, struct device *dev, int id,
		unsigned long base,
		u32 module, struct clk *clk_ipu)
{
	struct ipu_di *di;

	if (id > 1)
		return -ENODEV;

	di = devm_kzalloc(dev, sizeof(*di), GFP_KERNEL);
	if (!di)
		return -ENOMEM;

	ipu->di_priv[id] = di;

	di->clk_di = devm_clk_get(dev, id ? "di1" : "di0");
	if (IS_ERR(di->clk_di))
		return PTR_ERR(di->clk_di);

	di->module = module;
	di->id = id;
	di->clk_ipu = clk_ipu;
	di->base = devm_ioremap(dev, base, PAGE_SIZE);
	if (!di->base)
		return -ENOMEM;

	ipu_di_write(di, 0x10, DI_BS_CLKGEN0);

	dev_dbg(dev, "DI%d base: 0x%08lx remapped to %p\n",
			id, base, di->base);
	di->inuse = false;
	di->ipu = ipu;

	return 0;
}