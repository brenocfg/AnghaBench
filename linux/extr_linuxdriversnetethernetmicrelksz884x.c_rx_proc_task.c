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
struct ksz_hw {int /*<<< orphan*/  enabled; } ;
struct dev_info {int /*<<< orphan*/  rx_tasklet; int /*<<< orphan*/  hwlock; int /*<<< orphan*/  (* dev_rcv ) (struct dev_info*) ;struct ksz_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS884X_INT_RX ; 
 int /*<<< orphan*/  KS884X_INT_RX_MASK ; 
 int /*<<< orphan*/  hw_ack_intr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_resume_rx (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_turn_on_intr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dev_info*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rx_proc_task(unsigned long data)
{
	struct dev_info *hw_priv = (struct dev_info *) data;
	struct ksz_hw *hw = &hw_priv->hw;

	if (!hw->enabled)
		return;
	if (unlikely(!hw_priv->dev_rcv(hw_priv))) {

		/* In case receive process is suspended because of overrun. */
		hw_resume_rx(hw);

		/* tasklets are interruptible. */
		spin_lock_irq(&hw_priv->hwlock);
		hw_turn_on_intr(hw, KS884X_INT_RX_MASK);
		spin_unlock_irq(&hw_priv->hwlock);
	} else {
		hw_ack_intr(hw, KS884X_INT_RX);
		tasklet_schedule(&hw_priv->rx_tasklet);
	}
}