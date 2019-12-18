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
struct ksz_hw {int dummy; } ;
struct dev_info {int /*<<< orphan*/  hwlock; struct ksz_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS884X_INT_TX ; 
 int /*<<< orphan*/  KS884X_INT_TX_MASK ; 
 int /*<<< orphan*/  hw_ack_intr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_turn_on_intr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_done (struct dev_info*) ; 

__attribute__((used)) static void tx_proc_task(unsigned long data)
{
	struct dev_info *hw_priv = (struct dev_info *) data;
	struct ksz_hw *hw = &hw_priv->hw;

	hw_ack_intr(hw, KS884X_INT_TX_MASK);

	tx_done(hw_priv);

	/* tasklets are interruptible. */
	spin_lock_irq(&hw_priv->hwlock);
	hw_turn_on_intr(hw, KS884X_INT_TX);
	spin_unlock_irq(&hw_priv->hwlock);
}