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
struct sd {int bridge; scalar_t__ invert_led; } ;

/* Variables and functions */
#define  BRIDGE_OV511PLUS 131 
#define  BRIDGE_OV518 130 
#define  BRIDGE_OV518PLUS 129 
#define  BRIDGE_OV519 128 
 int /*<<< orphan*/  OV519_GPIO_DATA_OUT0 ; 
 int /*<<< orphan*/  R511_SYS_LED_CTL ; 
 int /*<<< orphan*/  R518_GPIO_OUT ; 
 int /*<<< orphan*/  reg_w (struct sd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w_mask (struct sd*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ov51x_led_control(struct sd *sd, int on)
{
	if (sd->invert_led)
		on = !on;

	switch (sd->bridge) {
	/* OV511 has no LED control */
	case BRIDGE_OV511PLUS:
		reg_w(sd, R511_SYS_LED_CTL, on);
		break;
	case BRIDGE_OV518:
	case BRIDGE_OV518PLUS:
		reg_w_mask(sd, R518_GPIO_OUT, 0x02 * on, 0x02);
		break;
	case BRIDGE_OV519:
		reg_w_mask(sd, OV519_GPIO_DATA_OUT0, on, 1);
		break;
	}
}