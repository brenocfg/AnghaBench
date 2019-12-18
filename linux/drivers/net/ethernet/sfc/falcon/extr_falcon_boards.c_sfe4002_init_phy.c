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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int QUAKE_LED_LINK_ACTSTAT ; 
 int QUAKE_LED_OFF ; 
 int QUAKE_LED_RXLINK ; 
 int QUAKE_LED_TXLINK ; 
 int /*<<< orphan*/  SFE4002_FAULT_LED ; 
 int /*<<< orphan*/  SFE4002_RX_LED ; 
 int /*<<< orphan*/  SFE4002_TX_LED ; 
 int /*<<< orphan*/  falcon_qt202x_set_led (struct ef4_nic*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sfe4002_init_phy(struct ef4_nic *efx)
{
	/* Set the TX and RX LEDs to reflect status and activity, and the
	 * fault LED off */
	falcon_qt202x_set_led(efx, SFE4002_TX_LED,
			      QUAKE_LED_TXLINK | QUAKE_LED_LINK_ACTSTAT);
	falcon_qt202x_set_led(efx, SFE4002_RX_LED,
			      QUAKE_LED_RXLINK | QUAKE_LED_LINK_ACTSTAT);
	falcon_qt202x_set_led(efx, SFE4002_FAULT_LED, QUAKE_LED_OFF);
}