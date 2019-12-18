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
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ bHWPowerdown; } ;
struct adapter {TYPE_1__ pwrctrlpriv; } ;
typedef  enum rt_rf_power_state { ____Placeholder_rt_rf_power_state } rt_rf_power_state ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBG_88E (char*,int) ; 
 int /*<<< orphan*/  REG_GPIO_IO_SEL ; 
 int /*<<< orphan*/  REG_HSISR ; 
 int /*<<< orphan*/  REG_MAC_PINMUX_CFG ; 
 int rf_off ; 
 int rf_on ; 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

enum rt_rf_power_state RfOnOffDetect(struct adapter *adapt)
{
	u8 val8;
	enum rt_rf_power_state rfpowerstate = rf_off;

	if (adapt->pwrctrlpriv.bHWPowerdown) {
		val8 = usb_read8(adapt, REG_HSISR);
		DBG_88E("pwrdown, 0x5c(BIT(7))=%02x\n", val8);
		rfpowerstate = (val8 & BIT(7)) ? rf_off : rf_on;
	} else { /*  rf on/off */
		usb_write8(adapt, REG_MAC_PINMUX_CFG, usb_read8(adapt, REG_MAC_PINMUX_CFG) & ~(BIT(3)));
		val8 = usb_read8(adapt, REG_GPIO_IO_SEL);
		DBG_88E("GPIO_IN=%02x\n", val8);
		rfpowerstate = (val8 & BIT(3)) ? rf_on : rf_off;
	}
	return rfpowerstate;
}