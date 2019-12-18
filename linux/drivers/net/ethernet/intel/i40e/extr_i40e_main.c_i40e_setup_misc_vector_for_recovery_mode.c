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
typedef  int /*<<< orphan*/  u32 ;
struct i40e_pf {int flags; TYPE_1__* pdev; int /*<<< orphan*/  int_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int I40E_FLAG_MSIX_ENABLED ; 
 int I40E_FLAG_MSI_ENABLED ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  i40e_enable_misc_int_causes (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_intr ; 
 int /*<<< orphan*/  i40e_irq_dynamic_enable_icr0 (struct i40e_pf*) ; 
 int i40e_setup_misc_vector (struct i40e_pf*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i40e_pf*) ; 

__attribute__((used)) static int i40e_setup_misc_vector_for_recovery_mode(struct i40e_pf *pf)
{
	int err;

	if (pf->flags & I40E_FLAG_MSIX_ENABLED) {
		err = i40e_setup_misc_vector(pf);

		if (err) {
			dev_info(&pf->pdev->dev,
				 "MSI-X misc vector request failed, error %d\n",
				 err);
			return err;
		}
	} else {
		u32 flags = pf->flags & I40E_FLAG_MSI_ENABLED ? 0 : IRQF_SHARED;

		err = request_irq(pf->pdev->irq, i40e_intr, flags,
				  pf->int_name, pf);

		if (err) {
			dev_info(&pf->pdev->dev,
				 "MSI/legacy misc vector request failed, error %d\n",
				 err);
			return err;
		}
		i40e_enable_misc_int_causes(pf);
		i40e_irq_dynamic_enable_icr0(pf);
	}

	return 0;
}