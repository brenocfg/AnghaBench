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
struct saa7146_pci_extension_data {int dummy; } ;
struct saa7146_dev {struct budget* ext_priv; } ;
struct TYPE_2__ {struct budget* priv; } ;
struct budget {TYPE_1__ dvb_adapter; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  dprintk (int,char*,struct saa7146_dev*,struct saa7146_pci_extension_data*,struct budget*) ; 
 int /*<<< orphan*/  frontend_init (struct budget*) ; 
 int /*<<< orphan*/  kfree (struct budget*) ; 
 struct budget* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int ttpci_budget_init (struct budget*,struct saa7146_dev*,struct saa7146_pci_extension_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttpci_budget_init_hooks (struct budget*) ; 

__attribute__((used)) static int budget_attach (struct saa7146_dev* dev, struct saa7146_pci_extension_data *info)
{
	struct budget *budget = NULL;
	int err;

	budget = kmalloc(sizeof(struct budget), GFP_KERNEL);
	if( NULL == budget ) {
		return -ENOMEM;
	}

	dprintk(2, "dev:%p, info:%p, budget:%p\n", dev, info, budget);

	dev->ext_priv = budget;

	err = ttpci_budget_init(budget, dev, info, THIS_MODULE, adapter_nr);
	if (err) {
		printk("==> failed\n");
		kfree (budget);
		return err;
	}

	budget->dvb_adapter.priv = budget;
	frontend_init(budget);

	ttpci_budget_init_hooks(budget);

	return 0;
}