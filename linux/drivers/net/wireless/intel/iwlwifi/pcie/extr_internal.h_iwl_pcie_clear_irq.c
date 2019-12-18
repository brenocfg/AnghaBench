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
struct msix_entry {int /*<<< orphan*/  entry; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_MSIX_AUTOMASK_ST_AD ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iwl_pcie_clear_irq(struct iwl_trans *trans,
				      struct msix_entry *entry)
{
	/*
	 * Before sending the interrupt the HW disables it to prevent
	 * a nested interrupt. This is done by writing 1 to the corresponding
	 * bit in the mask register. After handling the interrupt, it should be
	 * re-enabled by clearing this bit. This register is defined as
	 * write 1 clear (W1C) register, meaning that it's being clear
	 * by writing 1 to the bit.
	 */
	iwl_write32(trans, CSR_MSIX_AUTOMASK_ST_AD, BIT(entry->entry));
}