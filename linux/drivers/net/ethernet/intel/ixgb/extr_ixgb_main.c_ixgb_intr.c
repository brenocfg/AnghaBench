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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ixgb_hw {int dummy; } ;
struct ixgb_adapter {int /*<<< orphan*/  napi; struct ixgb_hw hw; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  IMC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int IXGB_INT_LSC ; 
 int IXGB_INT_RXSEQ ; 
 int IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (struct ixgb_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGB_DOWN ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t
ixgb_intr(int irq, void *data)
{
	struct net_device *netdev = data;
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	struct ixgb_hw *hw = &adapter->hw;
	u32 icr = IXGB_READ_REG(hw, ICR);

	if (unlikely(!icr))
		return IRQ_NONE;  /* Not our interrupt */

	if (unlikely(icr & (IXGB_INT_RXSEQ | IXGB_INT_LSC)))
		if (!test_bit(__IXGB_DOWN, &adapter->flags))
			mod_timer(&adapter->watchdog_timer, jiffies);

	if (napi_schedule_prep(&adapter->napi)) {

		/* Disable interrupts and register for poll. The flush
		  of the posted write is intentionally left out.
		*/

		IXGB_WRITE_REG(&adapter->hw, IMC, ~0);
		__napi_schedule(&adapter->napi);
	}
	return IRQ_HANDLED;
}