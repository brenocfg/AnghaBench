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
struct mwifiex_adapter {scalar_t__ irq_wakeup; scalar_t__ wake_by_wifi; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  disable_irq_wake (scalar_t__) ; 
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 

__attribute__((used)) static inline void mwifiex_disable_wake(struct mwifiex_adapter *adapter)
{
	if (adapter->irq_wakeup >= 0) {
		disable_irq_wake(adapter->irq_wakeup);
		disable_irq(adapter->irq_wakeup);
		if (adapter->wake_by_wifi)
			/* Undo our disable, since interrupt handler already
			 * did this.
			 */
			enable_irq(adapter->irq_wakeup);

	}
}