#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mcba_usb_msg_ka_can {scalar_t__ tx_err_cnt; scalar_t__ rx_err_cnt; scalar_t__ tx_bus_off; int /*<<< orphan*/  soft_ver_minor; int /*<<< orphan*/  soft_ver_major; } ;
struct TYPE_4__ {int /*<<< orphan*/  const bitrate; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; TYPE_1__ bittiming; } ;
struct TYPE_5__ {scalar_t__ txerr; scalar_t__ rxerr; } ;
struct mcba_priv {int can_ka_first_pass; int can_speed_check; TYPE_3__ can; TYPE_2__ bec; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_BUS_OFF ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_PASSIVE ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_WARNING ; 
 scalar_t__ MCBA_CAN_STATE_ERR_PSV_TH ; 
 scalar_t__ MCBA_CAN_STATE_WRN_TH ; 
 int /*<<< orphan*/  convert_can2host_bitrate (struct mcba_usb_msg_ka_can*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mcba_usb_process_ka_can(struct mcba_priv *priv,
				    struct mcba_usb_msg_ka_can *msg)
{
	if (unlikely(priv->can_ka_first_pass)) {
		netdev_info(priv->netdev, "PIC CAN version %hhu.%hhu\n",
			    msg->soft_ver_major, msg->soft_ver_minor);

		priv->can_ka_first_pass = false;
	}

	if (unlikely(priv->can_speed_check)) {
		const u32 bitrate = convert_can2host_bitrate(msg);

		priv->can_speed_check = false;

		if (bitrate != priv->can.bittiming.bitrate)
			netdev_err(
			    priv->netdev,
			    "Wrong bitrate reported by the device (%u). Expected %u",
			    bitrate, priv->can.bittiming.bitrate);
	}

	priv->bec.txerr = msg->tx_err_cnt;
	priv->bec.rxerr = msg->rx_err_cnt;

	if (msg->tx_bus_off)
		priv->can.state = CAN_STATE_BUS_OFF;

	else if ((priv->bec.txerr > MCBA_CAN_STATE_ERR_PSV_TH) ||
		 (priv->bec.rxerr > MCBA_CAN_STATE_ERR_PSV_TH))
		priv->can.state = CAN_STATE_ERROR_PASSIVE;

	else if ((priv->bec.txerr > MCBA_CAN_STATE_WRN_TH) ||
		 (priv->bec.rxerr > MCBA_CAN_STATE_WRN_TH))
		priv->can.state = CAN_STATE_ERROR_WARNING;
}