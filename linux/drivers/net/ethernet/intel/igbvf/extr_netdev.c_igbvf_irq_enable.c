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
struct igbvf_adapter {int /*<<< orphan*/  eims_enable_mask; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIAC ; 
 int /*<<< orphan*/  EIAM ; 
 int /*<<< orphan*/  EIMS ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igbvf_irq_enable(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	ew32(EIAC, adapter->eims_enable_mask);
	ew32(EIAM, adapter->eims_enable_mask);
	ew32(EIMS, adapter->eims_enable_mask);
}