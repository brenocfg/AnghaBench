#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct saa7146_pci_extension_data {int dummy; } ;
struct saa7146_dev {struct budget_ci* ext_priv; } ;
struct TYPE_5__ {struct budget_ci* priv; } ;
struct TYPE_6__ {TYPE_1__ dvb_adapter; } ;
struct budget_ci {TYPE_2__ budget; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  ciintf_init (struct budget_ci*) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct budget_ci*) ; 
 int /*<<< orphan*/  frontend_init (struct budget_ci*) ; 
 int /*<<< orphan*/  kfree (struct budget_ci*) ; 
 struct budget_ci* kzalloc (int,int /*<<< orphan*/ ) ; 
 int msp430_ir_init (struct budget_ci*) ; 
 int /*<<< orphan*/  ttpci_budget_deinit (TYPE_2__*) ; 
 int ttpci_budget_init (TYPE_2__*,struct saa7146_dev*,struct saa7146_pci_extension_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttpci_budget_init_hooks (TYPE_2__*) ; 

__attribute__((used)) static int budget_ci_attach(struct saa7146_dev *dev, struct saa7146_pci_extension_data *info)
{
	struct budget_ci *budget_ci;
	int err;

	budget_ci = kzalloc(sizeof(struct budget_ci), GFP_KERNEL);
	if (!budget_ci) {
		err = -ENOMEM;
		goto out1;
	}

	dprintk(2, "budget_ci: %p\n", budget_ci);

	dev->ext_priv = budget_ci;

	err = ttpci_budget_init(&budget_ci->budget, dev, info, THIS_MODULE,
				adapter_nr);
	if (err)
		goto out2;

	err = msp430_ir_init(budget_ci);
	if (err)
		goto out3;

	ciintf_init(budget_ci);

	budget_ci->budget.dvb_adapter.priv = budget_ci;
	frontend_init(budget_ci);

	ttpci_budget_init_hooks(&budget_ci->budget);

	return 0;

out3:
	ttpci_budget_deinit(&budget_ci->budget);
out2:
	kfree(budget_ci);
out1:
	return err;
}