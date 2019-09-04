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
struct cxl_afu {TYPE_1__* native; int /*<<< orphan*/  psl_irq_name; int /*<<< orphan*/  adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* release_one_irq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ psl_virq; int /*<<< orphan*/  psl_hwirq; } ;

/* Variables and functions */
 TYPE_2__* cxl_ops ; 
 int /*<<< orphan*/  cxl_unmap_irq (scalar_t__,struct cxl_afu*) ; 
 scalar_t__ irq_find_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cxl_native_release_psl_irq(struct cxl_afu *afu)
{
	if (afu->native->psl_virq == 0 ||
	    afu->native->psl_virq !=
	    irq_find_mapping(NULL, afu->native->psl_hwirq))
		return;

	cxl_unmap_irq(afu->native->psl_virq, afu);
	cxl_ops->release_one_irq(afu->adapter, afu->native->psl_hwirq);
	kfree(afu->psl_irq_name);
	afu->native->psl_virq = 0;
}