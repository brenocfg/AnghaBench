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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  stats; struct e1000_hw hw; } ;

/* Variables and functions */
 scalar_t__ TBI_ACCEPT (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_tbi_adjust_stats (struct e1000_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool e1000_tbi_should_accept(struct e1000_adapter *adapter,
				    u8 status, u8 errors,
				    u32 length, const u8 *data)
{
	struct e1000_hw *hw = &adapter->hw;
	u8 last_byte = *(data + length - 1);

	if (TBI_ACCEPT(hw, status, errors, length, last_byte)) {
		unsigned long irq_flags;

		spin_lock_irqsave(&adapter->stats_lock, irq_flags);
		e1000_tbi_adjust_stats(hw, &adapter->stats, length, data);
		spin_unlock_irqrestore(&adapter->stats_lock, irq_flags);

		return true;
	}

	return false;
}