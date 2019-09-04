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
struct pdc_state {scalar_t__ pdc_reg_vbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDC_INTMASK ; 
 scalar_t__ PDC_INTMASK_OFFSET ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pdc_receive (struct pdc_state*) ; 

__attribute__((used)) static void pdc_tasklet_cb(unsigned long data)
{
	struct pdc_state *pdcs = (struct pdc_state *)data;

	pdc_receive(pdcs);

	/* reenable interrupts */
	iowrite32(PDC_INTMASK, pdcs->pdc_reg_vbase + PDC_INTMASK_OFFSET);
}