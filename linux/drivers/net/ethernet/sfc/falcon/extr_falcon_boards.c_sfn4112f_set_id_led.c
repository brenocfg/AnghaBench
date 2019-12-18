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
typedef  enum ef4_led_mode { ____Placeholder_ef4_led_mode } ef4_led_mode ;

/* Variables and functions */
#define  EF4_LED_OFF 129 
#define  EF4_LED_ON 128 
 int QUAKE_LED_LINK_STAT ; 
 int QUAKE_LED_OFF ; 
 int QUAKE_LED_ON ; 
 int QUAKE_LED_RXLINK ; 
 int /*<<< orphan*/  SFN4112F_LINK_LED ; 
 int /*<<< orphan*/  falcon_qt202x_set_led (struct ef4_nic*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sfn4112f_set_id_led(struct ef4_nic *efx, enum ef4_led_mode mode)
{
	int reg;

	switch (mode) {
	case EF4_LED_OFF:
		reg = QUAKE_LED_OFF;
		break;
	case EF4_LED_ON:
		reg = QUAKE_LED_ON;
		break;
	default:
		reg = QUAKE_LED_RXLINK | QUAKE_LED_LINK_STAT;
		break;
	}

	falcon_qt202x_set_led(efx, SFN4112F_LINK_LED, reg);
}