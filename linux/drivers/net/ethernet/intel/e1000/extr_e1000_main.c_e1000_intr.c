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
struct e1000_hw {int get_link_status; } ;
struct e1000_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  napi; scalar_t__ total_rx_packets; scalar_t__ total_rx_bytes; scalar_t__ total_tx_packets; scalar_t__ total_tx_bytes; int /*<<< orphan*/  watchdog_task; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int E1000_ICR_LSC ; 
 int E1000_ICR_RXSEQ ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  IMC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_irq_enable (struct e1000_adapter*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t e1000_intr(int irq, void *data)
{
	struct net_device *netdev = data;
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 icr = er32(ICR);

	if (unlikely((!icr)))
		return IRQ_NONE;  /* Not our interrupt */

	/* we might have caused the interrupt, but the above
	 * read cleared it, and just in case the driver is
	 * down there is nothing to do so return handled
	 */
	if (unlikely(test_bit(__E1000_DOWN, &adapter->flags)))
		return IRQ_HANDLED;

	if (unlikely(icr & (E1000_ICR_RXSEQ | E1000_ICR_LSC))) {
		hw->get_link_status = 1;
		/* guard against interrupt when we're going down */
		if (!test_bit(__E1000_DOWN, &adapter->flags))
			schedule_delayed_work(&adapter->watchdog_task, 1);
	}

	/* disable interrupts, without the synchronize_irq bit */
	ew32(IMC, ~0);
	E1000_WRITE_FLUSH();

	if (likely(napi_schedule_prep(&adapter->napi))) {
		adapter->total_tx_bytes = 0;
		adapter->total_tx_packets = 0;
		adapter->total_rx_bytes = 0;
		adapter->total_rx_packets = 0;
		__napi_schedule(&adapter->napi);
	} else {
		/* this really should not happen! if it does it is basically a
		 * bug, but not a hard error, so enable ints and continue
		 */
		if (!test_bit(__E1000_DOWN, &adapter->flags))
			e1000_irq_enable(adapter);
	}

	return IRQ_HANDLED;
}