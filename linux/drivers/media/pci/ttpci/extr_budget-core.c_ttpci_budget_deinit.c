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
struct saa7146_dev {int /*<<< orphan*/  pci; } ;
struct budget {int /*<<< orphan*/  dvb_adapter; int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  pt; int /*<<< orphan*/  grabbing; int /*<<< orphan*/  vpe_tasklet; struct saa7146_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  budget_unregister (struct budget*) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct budget*) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7146_vfree_destroy_pgtable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

int ttpci_budget_deinit(struct budget *budget)
{
	struct saa7146_dev *dev = budget->dev;

	dprintk(2, "budget: %p\n", budget);

	budget_unregister(budget);

	tasklet_kill(&budget->vpe_tasklet);

	saa7146_vfree_destroy_pgtable(dev->pci, budget->grabbing, &budget->pt);

	i2c_del_adapter(&budget->i2c_adap);

	dvb_unregister_adapter(&budget->dvb_adapter);

	return 0;
}