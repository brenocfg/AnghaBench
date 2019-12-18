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
struct ipw_hardware {int /*<<< orphan*/  lock; scalar_t__ rx_ready; int /*<<< orphan*/  blocking_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_receive_packet (struct ipw_hardware*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int get_packets_from_hw(struct ipw_hardware *hw)
{
	int received = 0;
	unsigned long flags;

	spin_lock_irqsave(&hw->lock, flags);
	while (hw->rx_ready && !hw->blocking_rx) {
		received = 1;
		hw->rx_ready--;
		spin_unlock_irqrestore(&hw->lock, flags);

		do_receive_packet(hw);

		spin_lock_irqsave(&hw->lock, flags);
	}
	spin_unlock_irqrestore(&hw->lock, flags);

	return received;
}