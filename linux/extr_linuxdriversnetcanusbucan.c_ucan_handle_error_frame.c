#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct can_device_stats {int /*<<< orphan*/  error_warning; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  bus_off; int /*<<< orphan*/  bus_error; int /*<<< orphan*/  arbitration_lost; } ;
struct TYPE_7__ {int state; struct can_device_stats can_stats; } ;
struct ucan_priv {TYPE_4__* netdev; TYPE_3__ can; } ;
struct TYPE_5__ {int* data; } ;
struct TYPE_6__ {TYPE_1__ can_msg; } ;
struct ucan_message_in {TYPE_2__ msg; } ;
struct net_device_stats {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_over_errors; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;
typedef  int canid_t ;
struct TYPE_8__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int CAN_ERR_ACK ; 
 int CAN_ERR_BUSERROR ; 
 int CAN_ERR_BUSOFF ; 
 int CAN_ERR_CRTL ; 
 int CAN_ERR_CRTL_ACTIVE ; 
 int CAN_ERR_CRTL_RX_OVERFLOW ; 
 int CAN_ERR_CRTL_RX_PASSIVE ; 
 int CAN_ERR_CRTL_RX_WARNING ; 
 int CAN_ERR_CRTL_TX_PASSIVE ; 
 int CAN_ERR_CRTL_TX_WARNING ; 
 int CAN_ERR_LOSTARB ; 
 int CAN_ERR_PROT ; 
 int CAN_ERR_PROT_TX ; 
#define  CAN_STATE_BUS_OFF 130 
 int CAN_STATE_ERROR_ACTIVE ; 
#define  CAN_STATE_ERROR_PASSIVE 129 
#define  CAN_STATE_ERROR_WARNING 128 
 int /*<<< orphan*/  can_bus_off (TYPE_4__*) ; 

__attribute__((used)) static bool ucan_handle_error_frame(struct ucan_priv *up,
				    struct ucan_message_in *m,
				    canid_t canid)
{
	enum can_state new_state = up->can.state;
	struct net_device_stats *net_stats = &up->netdev->stats;
	struct can_device_stats *can_stats = &up->can.can_stats;

	if (canid & CAN_ERR_LOSTARB)
		can_stats->arbitration_lost++;

	if (canid & CAN_ERR_BUSERROR)
		can_stats->bus_error++;

	if (canid & CAN_ERR_ACK)
		net_stats->tx_errors++;

	if (canid & CAN_ERR_BUSOFF)
		new_state = CAN_STATE_BUS_OFF;

	/* controller problems, details in data[1] */
	if (canid & CAN_ERR_CRTL) {
		u8 d1 = m->msg.can_msg.data[1];

		if (d1 & CAN_ERR_CRTL_RX_OVERFLOW)
			net_stats->rx_over_errors++;

		/* controller state bits: if multiple are set the worst wins */
		if (d1 & CAN_ERR_CRTL_ACTIVE)
			new_state = CAN_STATE_ERROR_ACTIVE;

		if (d1 & (CAN_ERR_CRTL_RX_WARNING | CAN_ERR_CRTL_TX_WARNING))
			new_state = CAN_STATE_ERROR_WARNING;

		if (d1 & (CAN_ERR_CRTL_RX_PASSIVE | CAN_ERR_CRTL_TX_PASSIVE))
			new_state = CAN_STATE_ERROR_PASSIVE;
	}

	/* protocol error, details in data[2] */
	if (canid & CAN_ERR_PROT) {
		u8 d2 = m->msg.can_msg.data[2];

		if (d2 & CAN_ERR_PROT_TX)
			net_stats->tx_errors++;
		else
			net_stats->rx_errors++;
	}

	/* no state change - we are done */
	if (up->can.state == new_state)
		return false;

	/* we switched into a better state */
	if (up->can.state > new_state) {
		up->can.state = new_state;
		return true;
	}

	/* we switched into a worse state */
	up->can.state = new_state;
	switch (new_state) {
	case CAN_STATE_BUS_OFF:
		can_stats->bus_off++;
		can_bus_off(up->netdev);
		break;
	case CAN_STATE_ERROR_PASSIVE:
		can_stats->error_passive++;
		break;
	case CAN_STATE_ERROR_WARNING:
		can_stats->error_warning++;
		break;
	default:
		break;
	}
	return true;
}