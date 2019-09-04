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
struct i40e_hw {int dummy; } ;
struct i40e_pf {int /*<<< orphan*/  int_name; TYPE_2__* pdev; int /*<<< orphan*/  state; TYPE_1__* msix_entries; struct i40e_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  I40E_ITR_8K ; 
 int /*<<< orphan*/  I40E_PFINT_ITR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_PFINT_LNKLST0 ; 
 int /*<<< orphan*/  I40E_QUEUE_END_OF_LIST ; 
 int /*<<< orphan*/  I40E_RX_ITR ; 
 int /*<<< orphan*/  __I40E_MISC_IRQ_REQUESTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40e_enable_misc_int_causes (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_intr ; 
 int /*<<< orphan*/  i40e_irq_dynamic_enable_icr0 (struct i40e_pf*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i40e_pf*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_setup_misc_vector(struct i40e_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	int err = 0;

	/* Only request the IRQ once, the first time through. */
	if (!test_and_set_bit(__I40E_MISC_IRQ_REQUESTED, pf->state)) {
		err = request_irq(pf->msix_entries[0].vector,
				  i40e_intr, 0, pf->int_name, pf);
		if (err) {
			clear_bit(__I40E_MISC_IRQ_REQUESTED, pf->state);
			dev_info(&pf->pdev->dev,
				 "request_irq for %s failed: %d\n",
				 pf->int_name, err);
			return -EFAULT;
		}
	}

	i40e_enable_misc_int_causes(pf);

	/* associate no queues to the misc vector */
	wr32(hw, I40E_PFINT_LNKLST0, I40E_QUEUE_END_OF_LIST);
	wr32(hw, I40E_PFINT_ITR0(I40E_RX_ITR), I40E_ITR_8K);

	i40e_flush(hw);

	i40e_irq_dynamic_enable_icr0(pf);

	return err;
}