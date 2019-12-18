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
struct ipw_priv {int status; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int STATUS_EXIT_PENDING ; 
 int STATUS_RF_KILL_MASK ; 
 int /*<<< orphan*/  ipw_deinit (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_disable_interrupts (struct ipw_priv*) ; 
 scalar_t__ ipw_is_init (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_led_radio_off (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_stop_nic (struct ipw_priv*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw_down(struct ipw_priv *priv)
{
	int exit_pending = priv->status & STATUS_EXIT_PENDING;

	priv->status |= STATUS_EXIT_PENDING;

	if (ipw_is_init(priv))
		ipw_deinit(priv);

	/* Wipe out the EXIT_PENDING status bit if we are not actually
	 * exiting the module */
	if (!exit_pending)
		priv->status &= ~STATUS_EXIT_PENDING;

	/* tell the device to stop sending interrupts */
	ipw_disable_interrupts(priv);

	/* Clear all bits but the RF Kill */
	priv->status &= STATUS_RF_KILL_MASK | STATUS_EXIT_PENDING;
	netif_carrier_off(priv->net_dev);

	ipw_stop_nic(priv);

	ipw_led_radio_off(priv);
}