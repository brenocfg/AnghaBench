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
struct mwifiex_adapter {scalar_t__ irq_wakeup; int wake_by_wifi; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 int /*<<< orphan*/  enable_irq_wake (scalar_t__) ; 

__attribute__((used)) static inline void mwifiex_enable_wake(struct mwifiex_adapter *adapter)
{
	/* Enable platform specific wakeup interrupt */
	if (adapter->irq_wakeup >= 0) {
		adapter->wake_by_wifi = false;
		enable_irq(adapter->irq_wakeup);
		enable_irq_wake(adapter->irq_wakeup);
	}
}