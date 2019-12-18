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
struct ipw_hardware {int to_setup; int /*<<< orphan*/  lock; scalar_t__ shutting_down; } ;

/* Variables and functions */
 int PRIO_SETUP ; 
 int get_current_packet_priority (struct ipw_hardware*) ; 
 int get_packets_from_hw (struct ipw_hardware*) ; 
 int /*<<< orphan*/  ipw_send_setup_packet (struct ipw_hardware*) ; 
 int /*<<< orphan*/  ipw_setup_hardware (struct ipw_hardware*) ; 
 int send_pending_packet (struct ipw_hardware*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ipwireless_do_tasklet(unsigned long hw_)
{
	struct ipw_hardware *hw = (struct ipw_hardware *) hw_;
	unsigned long flags;

	spin_lock_irqsave(&hw->lock, flags);
	if (hw->shutting_down) {
		spin_unlock_irqrestore(&hw->lock, flags);
		return;
	}

	if (hw->to_setup == 1) {
		/*
		 * Initial setup data sent to hardware
		 */
		hw->to_setup = 2;
		spin_unlock_irqrestore(&hw->lock, flags);

		ipw_setup_hardware(hw);
		ipw_send_setup_packet(hw);

		send_pending_packet(hw, PRIO_SETUP + 1);
		get_packets_from_hw(hw);
	} else {
		int priority_limit = get_current_packet_priority(hw);
		int again;

		spin_unlock_irqrestore(&hw->lock, flags);

		do {
			again = send_pending_packet(hw, priority_limit);
			again |= get_packets_from_hw(hw);
		} while (again);
	}
}