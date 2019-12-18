#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  restart_ms; struct net_device* dev; } ;
struct kvaser_pciefd_can {TYPE_1__ can; int /*<<< orphan*/  lock; } ;
struct can_frame {int dummy; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int CAN_STATE_BUS_OFF ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 int /*<<< orphan*/  can_change_state (struct net_device*,struct can_frame*,int,int) ; 
 int /*<<< orphan*/  kvaser_pciefd_start_controller_flush (struct kvaser_pciefd_can*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void kvaser_pciefd_change_state(struct kvaser_pciefd_can *can,
				       struct can_frame *cf,
				       enum can_state new_state,
				       enum can_state tx_state,
				       enum can_state rx_state)
{
	can_change_state(can->can.dev, cf, tx_state, rx_state);

	if (new_state == CAN_STATE_BUS_OFF) {
		struct net_device *ndev = can->can.dev;
		unsigned long irq_flags;

		spin_lock_irqsave(&can->lock, irq_flags);
		netif_stop_queue(can->can.dev);
		spin_unlock_irqrestore(&can->lock, irq_flags);

		/* Prevent CAN controller from auto recover from bus off */
		if (!can->can.restart_ms) {
			kvaser_pciefd_start_controller_flush(can);
			can_bus_off(ndev);
		}
	}
}