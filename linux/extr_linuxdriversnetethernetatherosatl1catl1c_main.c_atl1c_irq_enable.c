#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int intr_mask; } ;
struct atl1c_adapter {TYPE_1__ hw; int /*<<< orphan*/  irq_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_FLUSH (TYPE_1__*) ; 
 int /*<<< orphan*/  AT_WRITE_REG (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_IMR ; 
 int /*<<< orphan*/  REG_ISR ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void atl1c_irq_enable(struct atl1c_adapter *adapter)
{
	if (likely(atomic_dec_and_test(&adapter->irq_sem))) {
		AT_WRITE_REG(&adapter->hw, REG_ISR, 0x7FFFFFFF);
		AT_WRITE_REG(&adapter->hw, REG_IMR, adapter->hw.intr_mask);
		AT_WRITE_FLUSH(&adapter->hw);
	}
}