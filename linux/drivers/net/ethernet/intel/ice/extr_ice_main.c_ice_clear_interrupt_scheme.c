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
struct ice_pf {int /*<<< orphan*/ * irq_tracker; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_dis_msix (struct ice_pf*) ; 

__attribute__((used)) static void ice_clear_interrupt_scheme(struct ice_pf *pf)
{
	ice_dis_msix(pf);

	if (pf->irq_tracker) {
		devm_kfree(&pf->pdev->dev, pf->irq_tracker);
		pf->irq_tracker = NULL;
	}
}