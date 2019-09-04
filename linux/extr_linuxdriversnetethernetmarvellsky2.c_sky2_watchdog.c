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
struct timer_list {int dummy; } ;
struct sky2_hw {int ports; int flags; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  restart_work; struct net_device** dev; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_ISRC ; 
 scalar_t__ HZ ; 
 int SKY2_HW_RAM_BUFFER ; 
 struct sky2_hw* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct sky2_hw* hw ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ sky2_rx_hung (struct net_device*) ; 
 int /*<<< orphan*/  watchdog_timer ; 

__attribute__((used)) static void sky2_watchdog(struct timer_list *t)
{
	struct sky2_hw *hw = from_timer(hw, t, watchdog_timer);

	/* Check for lost IRQ once a second */
	if (sky2_read32(hw, B0_ISRC)) {
		napi_schedule(&hw->napi);
	} else {
		int i, active = 0;

		for (i = 0; i < hw->ports; i++) {
			struct net_device *dev = hw->dev[i];
			if (!netif_running(dev))
				continue;
			++active;

			/* For chips with Rx FIFO, check if stuck */
			if ((hw->flags & SKY2_HW_RAM_BUFFER) &&
			     sky2_rx_hung(dev)) {
				netdev_info(dev, "receiver hang detected\n");
				schedule_work(&hw->restart_work);
				return;
			}
		}

		if (active == 0)
			return;
	}

	mod_timer(&hw->watchdog_timer, round_jiffies(jiffies + HZ));
}