#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ice_pf {int num_avail_sw_msix; TYPE_2__* irq_tracker; TYPE_1__* pdev; } ;
struct TYPE_4__ {int num_entries; int end; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_dis_msix (struct ice_pf*) ; 
 int ice_ena_msix_range (struct ice_pf*) ; 

__attribute__((used)) static int ice_init_interrupt_scheme(struct ice_pf *pf)
{
	int vectors;

	vectors = ice_ena_msix_range(pf);

	if (vectors < 0)
		return vectors;

	/* set up vector assignment tracking */
	pf->irq_tracker =
		devm_kzalloc(&pf->pdev->dev, sizeof(*pf->irq_tracker) +
			     (sizeof(u16) * vectors), GFP_KERNEL);
	if (!pf->irq_tracker) {
		ice_dis_msix(pf);
		return -ENOMEM;
	}

	/* populate SW interrupts pool with number of OS granted IRQs. */
	pf->num_avail_sw_msix = vectors;
	pf->irq_tracker->num_entries = vectors;
	pf->irq_tracker->end = pf->irq_tracker->num_entries;

	return 0;
}