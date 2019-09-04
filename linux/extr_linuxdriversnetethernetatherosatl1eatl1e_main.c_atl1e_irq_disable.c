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
struct atl1e_adapter {TYPE_1__* pdev; int /*<<< orphan*/  hw; int /*<<< orphan*/  irq_sem; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_FLUSH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AT_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_IMR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void atl1e_irq_disable(struct atl1e_adapter *adapter)
{
	atomic_inc(&adapter->irq_sem);
	AT_WRITE_REG(&adapter->hw, REG_IMR, 0);
	AT_WRITE_FLUSH(&adapter->hw);
	synchronize_irq(adapter->pdev->irq);
}