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
struct cxl_afu {int /*<<< orphan*/ * psl_irq_name; TYPE_1__* native; int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  psl_virq; int /*<<< orphan*/  psl_hwirq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cxl_register_one_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cxl_afu*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  native_irq_multiplexed ; 

int cxl_native_register_psl_irq(struct cxl_afu *afu)
{
	int rc;

	afu->psl_irq_name = kasprintf(GFP_KERNEL, "cxl-%s",
				      dev_name(&afu->dev));
	if (!afu->psl_irq_name)
		return -ENOMEM;

	if ((rc = cxl_register_one_irq(afu->adapter, native_irq_multiplexed,
				    afu, &afu->native->psl_hwirq, &afu->native->psl_virq,
				    afu->psl_irq_name))) {
		kfree(afu->psl_irq_name);
		afu->psl_irq_name = NULL;
	}
	return rc;
}