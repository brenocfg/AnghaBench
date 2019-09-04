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
struct cxl {TYPE_1__* native; int /*<<< orphan*/ * irq_name; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int err_hwirq; int /*<<< orphan*/  err_virq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_ErrIVTE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cxl_p1_write (struct cxl*,int /*<<< orphan*/ ,int) ; 
 int cxl_register_one_irq (struct cxl*,int /*<<< orphan*/ ,struct cxl*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  native_irq_err ; 

int cxl_native_register_psl_err_irq(struct cxl *adapter)
{
	int rc;

	adapter->irq_name = kasprintf(GFP_KERNEL, "cxl-%s-err",
				      dev_name(&adapter->dev));
	if (!adapter->irq_name)
		return -ENOMEM;

	if ((rc = cxl_register_one_irq(adapter, native_irq_err, adapter,
				       &adapter->native->err_hwirq,
				       &adapter->native->err_virq,
				       adapter->irq_name))) {
		kfree(adapter->irq_name);
		adapter->irq_name = NULL;
		return rc;
	}

	cxl_p1_write(adapter, CXL_PSL_ErrIVTE, adapter->native->err_hwirq & 0xffff);

	return 0;
}