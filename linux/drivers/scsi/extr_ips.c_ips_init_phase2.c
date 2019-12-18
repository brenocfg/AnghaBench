#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int max_cmds; TYPE_9__* pcidev; int /*<<< orphan*/  active; } ;
typedef  TYPE_1__ ips_ha_t ;
struct TYPE_11__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_PRINTK (int /*<<< orphan*/ ,TYPE_9__*,char*) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  do_ipsintr ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ips_abort_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ips_allocatescbs (TYPE_1__*) ; 
 int /*<<< orphan*/  ips_deallocatescbs (TYPE_1__*,int) ; 
 TYPE_1__** ips_ha ; 
 int /*<<< orphan*/  ips_hainit (TYPE_1__*) ; 
 int /*<<< orphan*/  ips_name ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
ips_init_phase2(int index)
{
	ips_ha_t *ha;

	ha = ips_ha[index];

	METHOD_TRACE("ips_init_phase2", 1);
	if (!ha->active) {
		ips_ha[index] = NULL;
		return -1;
	}

	/* Install the interrupt handler */
	if (request_irq(ha->pcidev->irq, do_ipsintr, IRQF_SHARED, ips_name, ha)) {
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Unable to install interrupt handler\n");
		return ips_abort_init(ha, index);
	}

	/*
	 * Allocate a temporary SCB for initialization
	 */
	ha->max_cmds = 1;
	if (!ips_allocatescbs(ha)) {
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Unable to allocate a CCB\n");
		free_irq(ha->pcidev->irq, ha);
		return ips_abort_init(ha, index);
	}

	if (!ips_hainit(ha)) {
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Unable to initialize controller\n");
		free_irq(ha->pcidev->irq, ha);
		return ips_abort_init(ha, index);
	}
	/* Free the temporary SCB */
	ips_deallocatescbs(ha, 1);

	/* allocate CCBs */
	if (!ips_allocatescbs(ha)) {
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Unable to allocate CCBs\n");
		free_irq(ha->pcidev->irq, ha);
		return ips_abort_init(ha, index);
	}

	return SUCCESS;
}