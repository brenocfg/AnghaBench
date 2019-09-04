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
struct e1000_hw {int dummy; } ;
struct e1000_adapter {TYPE_1__* pdev; struct e1000_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  IMC ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_irq_disable(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	ew32(IMC, ~0);
	E1000_WRITE_FLUSH();
	synchronize_irq(adapter->pdev->irq);
}