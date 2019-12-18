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
struct atmel_private {int station_state; scalar_t__ last_beacon_timestamp; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int STATION_STATE_READY ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_enter_state(struct atmel_private *priv, int new_state)
{
	int old_state = priv->station_state;

	if (new_state == old_state)
		return;

	priv->station_state = new_state;

	if (new_state == STATION_STATE_READY) {
		netif_start_queue(priv->dev);
		netif_carrier_on(priv->dev);
	}

	if (old_state == STATION_STATE_READY) {
		netif_carrier_off(priv->dev);
		if (netif_running(priv->dev))
			netif_stop_queue(priv->dev);
		priv->last_beacon_timestamp = 0;
	}
}