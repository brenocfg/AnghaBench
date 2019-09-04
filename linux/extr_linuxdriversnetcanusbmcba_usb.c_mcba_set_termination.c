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
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct mcba_usb_msg_termination {int termination; int /*<<< orphan*/  cmd_id; } ;
struct mcba_usb_msg {int dummy; } ;
struct mcba_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBCA_CMD_SETUP_TERMINATION_RESISTANCE ; 
 scalar_t__ MCBA_TERMINATION_ENABLED ; 
 int /*<<< orphan*/  mcba_usb_xmit_cmd (struct mcba_priv*,struct mcba_usb_msg*) ; 
 struct mcba_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mcba_set_termination(struct net_device *netdev, u16 term)
{
	struct mcba_priv *priv = netdev_priv(netdev);
	struct mcba_usb_msg_termination usb_msg = {
		.cmd_id = MBCA_CMD_SETUP_TERMINATION_RESISTANCE
	};

	if (term == MCBA_TERMINATION_ENABLED)
		usb_msg.termination = 1;
	else
		usb_msg.termination = 0;

	mcba_usb_xmit_cmd(priv, (struct mcba_usb_msg *)&usb_msg);

	return 0;
}