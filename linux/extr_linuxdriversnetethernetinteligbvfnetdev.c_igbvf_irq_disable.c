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
struct e1000_hw {int dummy; } ;
struct igbvf_adapter {scalar_t__ msix_entries; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIAC ; 
 int /*<<< orphan*/  EIMC ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igbvf_irq_disable(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	ew32(EIMC, ~0);

	if (adapter->msix_entries)
		ew32(EIAC, 0);
}