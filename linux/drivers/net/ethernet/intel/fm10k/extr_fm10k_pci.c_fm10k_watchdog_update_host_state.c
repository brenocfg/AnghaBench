#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ (* get_host_state ) (struct fm10k_hw*,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mac; } ;
struct fm10k_intfc {int host_ready; int /*<<< orphan*/  flags; int /*<<< orphan*/  last_reset; int /*<<< orphan*/  state; int /*<<< orphan*/  link_down_event; struct fm10k_hw hw; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_FLAG_RESET_REQUESTED ; 
 int /*<<< orphan*/  FM10K_FLAG_SWPRI_CONFIG ; 
 int /*<<< orphan*/  __FM10K_LINK_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_configure_swpri_map (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_lock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_unlock (struct fm10k_intfc*) ; 
 scalar_t__ rtnl_trylock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct fm10k_hw*,int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_is_after_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_is_before_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_watchdog_update_host_state(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;
	s32 err;

	if (test_bit(__FM10K_LINK_DOWN, interface->state)) {
		interface->host_ready = false;
		if (time_is_after_jiffies(interface->link_down_event))
			return;
		clear_bit(__FM10K_LINK_DOWN, interface->state);
	}

	if (test_bit(FM10K_FLAG_SWPRI_CONFIG, interface->flags)) {
		if (rtnl_trylock()) {
			fm10k_configure_swpri_map(interface);
			rtnl_unlock();
		}
	}

	/* lock the mailbox for transmit and receive */
	fm10k_mbx_lock(interface);

	err = hw->mac.ops.get_host_state(hw, &interface->host_ready);
	if (err && time_is_before_jiffies(interface->last_reset))
		set_bit(FM10K_FLAG_RESET_REQUESTED, interface->flags);

	/* free the lock */
	fm10k_mbx_unlock(interface);
}