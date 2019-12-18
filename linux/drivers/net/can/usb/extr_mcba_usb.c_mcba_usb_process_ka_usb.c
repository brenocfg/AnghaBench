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
struct mcba_usb_msg_ka_usb {scalar_t__ termination_state; int /*<<< orphan*/  soft_ver_minor; int /*<<< orphan*/  soft_ver_major; } ;
struct TYPE_2__ {int /*<<< orphan*/  termination; } ;
struct mcba_priv {int usb_ka_first_pass; TYPE_1__ can; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCBA_TERMINATION_DISABLED ; 
 int /*<<< orphan*/  MCBA_TERMINATION_ENABLED ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mcba_usb_process_ka_usb(struct mcba_priv *priv,
				    struct mcba_usb_msg_ka_usb *msg)
{
	if (unlikely(priv->usb_ka_first_pass)) {
		netdev_info(priv->netdev, "PIC USB version %hhu.%hhu\n",
			    msg->soft_ver_major, msg->soft_ver_minor);

		priv->usb_ka_first_pass = false;
	}

	if (msg->termination_state)
		priv->can.termination = MCBA_TERMINATION_ENABLED;
	else
		priv->can.termination = MCBA_TERMINATION_DISABLED;
}