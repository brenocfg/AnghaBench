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
struct adapter {int /*<<< orphan*/  pdev_dev; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpumask_local_spread (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned short,int) ; 
 int irq_set_affinity_hint (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cxgb4_set_msix_aff(struct adapter *adap, unsigned short vec,
		       cpumask_var_t *aff_mask, int idx)
{
	int rv;

	if (!zalloc_cpumask_var(aff_mask, GFP_KERNEL)) {
		dev_err(adap->pdev_dev, "alloc_cpumask_var failed\n");
		return -ENOMEM;
	}

	cpumask_set_cpu(cpumask_local_spread(idx, dev_to_node(adap->pdev_dev)),
			*aff_mask);

	rv = irq_set_affinity_hint(vec, *aff_mask);
	if (rv)
		dev_warn(adap->pdev_dev,
			 "irq_set_affinity_hint %u failed %d\n",
			 vec, rv);

	return 0;
}