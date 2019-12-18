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
struct cxl_afu {scalar_t__ serr_virq; int /*<<< orphan*/  err_irq_name; int /*<<< orphan*/  serr_hwirq; int /*<<< orphan*/  adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release_one_irq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_SERR_An ; 
 TYPE_1__* cxl_ops ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cxl_unmap_irq (scalar_t__,struct cxl_afu*) ; 
 scalar_t__ irq_find_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cxl_native_release_serr_irq(struct cxl_afu *afu)
{
	if (afu->serr_virq == 0 ||
	    afu->serr_virq != irq_find_mapping(NULL, afu->serr_hwirq))
		return;

	cxl_p1n_write(afu, CXL_PSL_SERR_An, 0x0000000000000000);
	cxl_unmap_irq(afu->serr_virq, afu);
	cxl_ops->release_one_irq(afu->adapter, afu->serr_hwirq);
	kfree(afu->err_irq_name);
	afu->serr_virq = 0;
}