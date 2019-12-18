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
typedef  int /*<<< orphan*/  u16 ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_max_rx_irqs (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_tx_irqs (struct be_adapter*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 be_max_any_irqs(struct be_adapter *adapter)
{
	return max(be_max_tx_irqs(adapter), be_max_rx_irqs(adapter));
}