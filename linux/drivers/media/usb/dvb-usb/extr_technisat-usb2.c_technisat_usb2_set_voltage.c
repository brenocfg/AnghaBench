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
struct dvb_frontend {int dummy; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;
struct TYPE_2__ {scalar_t__ (* set_gpio ) (struct dvb_frontend*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EREMOTEIO ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 scalar_t__ stub1 (struct dvb_frontend*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ technisat_usb2_stv090x_config ; 

__attribute__((used)) static int technisat_usb2_set_voltage(struct dvb_frontend *fe,
				      enum fe_sec_voltage voltage)
{
	int i;
	u8 gpio[3] = { 0 }; /* 0 = 2, 1 = 3, 2 = 4 */

	gpio[2] = 1; /* high - voltage ? */

	switch (voltage) {
	case SEC_VOLTAGE_13:
		gpio[0] = 1;
		break;
	case SEC_VOLTAGE_18:
		gpio[0] = 1;
		gpio[1] = 1;
		break;
	default:
	case SEC_VOLTAGE_OFF:
		break;
	}

	for (i = 0; i < 3; i++)
		if (technisat_usb2_stv090x_config.set_gpio(fe, i+2, 0,
							   gpio[i], 0) != 0)
			return -EREMOTEIO;
	return 0;
}