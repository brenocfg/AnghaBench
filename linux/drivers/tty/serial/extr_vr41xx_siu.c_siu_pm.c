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
struct uart_port {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSIU_CLOCK ; 
#define  PORT_VR41XX_DSIU 129 
#define  PORT_VR41XX_SIU 128 
 int /*<<< orphan*/  SIU_CLOCK ; 
 int /*<<< orphan*/  vr41xx_mask_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vr41xx_supply_clock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void siu_pm(struct uart_port *port, unsigned int state, unsigned int oldstate)
{
	switch (state) {
	case 0:
		switch (port->type) {
		case PORT_VR41XX_SIU:
			vr41xx_supply_clock(SIU_CLOCK);
			break;
		case PORT_VR41XX_DSIU:
			vr41xx_supply_clock(DSIU_CLOCK);
			break;
		}
		break;
	case 3:
		switch (port->type) {
		case PORT_VR41XX_SIU:
			vr41xx_mask_clock(SIU_CLOCK);
			break;
		case PORT_VR41XX_DSIU:
			vr41xx_mask_clock(DSIU_CLOCK);
			break;
		}
		break;
	}
}