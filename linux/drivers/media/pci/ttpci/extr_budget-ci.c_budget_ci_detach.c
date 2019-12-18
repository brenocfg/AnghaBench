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
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct TYPE_2__ {scalar_t__ dvb_frontend; scalar_t__ ci_present; struct saa7146_dev* dev; } ;
struct budget_ci {TYPE_1__ budget; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7146_GPIO_INPUT ; 
 int /*<<< orphan*/  ciintf_deinit (struct budget_ci*) ; 
 int /*<<< orphan*/  dvb_frontend_detach (scalar_t__) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct budget_ci*) ; 
 int /*<<< orphan*/  msp430_ir_deinit (struct budget_ci*) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int ttpci_budget_deinit (TYPE_1__*) ; 

__attribute__((used)) static int budget_ci_detach(struct saa7146_dev *dev)
{
	struct budget_ci *budget_ci = (struct budget_ci *) dev->ext_priv;
	struct saa7146_dev *saa = budget_ci->budget.dev;
	int err;

	if (budget_ci->budget.ci_present)
		ciintf_deinit(budget_ci);
	msp430_ir_deinit(budget_ci);
	if (budget_ci->budget.dvb_frontend) {
		dvb_unregister_frontend(budget_ci->budget.dvb_frontend);
		dvb_frontend_detach(budget_ci->budget.dvb_frontend);
	}
	err = ttpci_budget_deinit(&budget_ci->budget);

	// disable frontend and CI interface
	saa7146_setgpio(saa, 2, SAA7146_GPIO_INPUT);

	kfree(budget_ci);

	return err;
}