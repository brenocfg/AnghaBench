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
struct mcba_usb_msg_ka_usb {int dummy; } ;
struct mcba_usb_msg_ka_can {int dummy; } ;
struct mcba_usb_msg_can {int dummy; } ;
struct mcba_usb_msg {int cmd_id; } ;
struct mcba_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
#define  MBCA_CMD_I_AM_ALIVE_FROM_CAN 132 
#define  MBCA_CMD_I_AM_ALIVE_FROM_USB 131 
#define  MBCA_CMD_NOTHING_TO_SEND 130 
#define  MBCA_CMD_RECEIVE_MESSAGE 129 
#define  MBCA_CMD_TRANSMIT_MESSAGE_RSP 128 
 int /*<<< orphan*/  mcba_usb_process_can (struct mcba_priv*,struct mcba_usb_msg_can*) ; 
 int /*<<< orphan*/  mcba_usb_process_ka_can (struct mcba_priv*,struct mcba_usb_msg_ka_can*) ; 
 int /*<<< orphan*/  mcba_usb_process_ka_usb (struct mcba_priv*,struct mcba_usb_msg_ka_usb*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void mcba_usb_process_rx(struct mcba_priv *priv,
				struct mcba_usb_msg *msg)
{
	switch (msg->cmd_id) {
	case MBCA_CMD_I_AM_ALIVE_FROM_CAN:
		mcba_usb_process_ka_can(priv,
					(struct mcba_usb_msg_ka_can *)msg);
		break;

	case MBCA_CMD_I_AM_ALIVE_FROM_USB:
		mcba_usb_process_ka_usb(priv,
					(struct mcba_usb_msg_ka_usb *)msg);
		break;

	case MBCA_CMD_RECEIVE_MESSAGE:
		mcba_usb_process_can(priv, (struct mcba_usb_msg_can *)msg);
		break;

	case MBCA_CMD_NOTHING_TO_SEND:
		/* Side effect of communication between PIC_USB and PIC_CAN.
		 * PIC_CAN is telling us that it has nothing to send
		 */
		break;

	case MBCA_CMD_TRANSMIT_MESSAGE_RSP:
		/* Transmission response from the device containing timestamp */
		break;

	default:
		netdev_warn(priv->netdev, "Unsupported msg (0x%hhX)",
			    msg->cmd_id);
		break;
	}
}