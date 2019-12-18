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
struct TYPE_2__ {int /*<<< orphan*/  accessory; int /*<<< orphan*/  usb_pd; } ;
struct tcpm_port {int connected; TYPE_1__ partner_desc; int /*<<< orphan*/  typec_port; int /*<<< orphan*/  partner; int /*<<< orphan*/  pd_capable; int /*<<< orphan*/  partner_ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPEC_ACCESSORY_AUDIO ; 
 int /*<<< orphan*/  TYPEC_ACCESSORY_DEBUG ; 
 int /*<<< orphan*/  TYPEC_ACCESSORY_NONE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcpm_port_is_audio (struct tcpm_port*) ; 
 scalar_t__ tcpm_port_is_debug (struct tcpm_port*) ; 
 int /*<<< orphan*/  typec_register_partner (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void tcpm_typec_connect(struct tcpm_port *port)
{
	if (!port->connected) {
		/* Make sure we don't report stale identity information */
		memset(&port->partner_ident, 0, sizeof(port->partner_ident));
		port->partner_desc.usb_pd = port->pd_capable;
		if (tcpm_port_is_debug(port))
			port->partner_desc.accessory = TYPEC_ACCESSORY_DEBUG;
		else if (tcpm_port_is_audio(port))
			port->partner_desc.accessory = TYPEC_ACCESSORY_AUDIO;
		else
			port->partner_desc.accessory = TYPEC_ACCESSORY_NONE;
		port->partner = typec_register_partner(port->typec_port,
						       &port->partner_desc);
		port->connected = true;
	}
}