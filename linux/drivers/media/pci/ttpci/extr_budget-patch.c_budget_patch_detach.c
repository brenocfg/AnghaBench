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
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct budget_patch {scalar_t__ dvb_frontend; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_frontend_detach (scalar_t__) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct budget_patch*) ; 
 int ttpci_budget_deinit (struct budget_patch*) ; 

__attribute__((used)) static int budget_patch_detach (struct saa7146_dev* dev)
{
	struct budget_patch *budget = (struct budget_patch*) dev->ext_priv;
	int err;

	if (budget->dvb_frontend) {
		dvb_unregister_frontend(budget->dvb_frontend);
		dvb_frontend_detach(budget->dvb_frontend);
	}
	err = ttpci_budget_deinit (budget);

	kfree (budget);

	return err;
}