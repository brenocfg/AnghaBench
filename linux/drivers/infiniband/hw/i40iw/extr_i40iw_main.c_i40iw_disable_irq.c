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
struct i40iw_sc_dev {int /*<<< orphan*/  hw; scalar_t__ is_pf; } ;
struct i40iw_msix_vector {int /*<<< orphan*/  irq; scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFINT_DYN_CTLN (scalar_t__) ; 
 int /*<<< orphan*/  I40E_VFINT_DYN_CTLN1 (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  i40iw_wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40iw_disable_irq(struct i40iw_sc_dev *dev,
			      struct i40iw_msix_vector *msix_vec,
			      void *dev_id)
{
	if (dev->is_pf)
		i40iw_wr32(dev->hw, I40E_PFINT_DYN_CTLN(msix_vec->idx - 1), 0);
	else
		i40iw_wr32(dev->hw, I40E_VFINT_DYN_CTLN1(msix_vec->idx - 1), 0);
	irq_set_affinity_hint(msix_vec->irq, NULL);
	free_irq(msix_vec->irq, dev_id);
}