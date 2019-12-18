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
struct i2400m {scalar_t__ state; } ;
typedef  enum wimax_rf_state { ____Placeholder_wimax_rf_state } wimax_rf_state ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 scalar_t__ I2400M_SS_RF_OFF ; 
 scalar_t__ I2400M_SS_RF_SHUTDOWN ; 
 int WIMAX_RF_OFF ; 
 int WIMAX_RF_ON ; 

__attribute__((used)) static
int i2400m_radio_is(struct i2400m *i2400m, enum wimax_rf_state state)
{
	if (state == WIMAX_RF_OFF)
		return i2400m->state == I2400M_SS_RF_OFF
			|| i2400m->state == I2400M_SS_RF_SHUTDOWN;
	else if (state == WIMAX_RF_ON)
		/* state == WIMAX_RF_ON */
		return i2400m->state != I2400M_SS_RF_OFF
			&& i2400m->state != I2400M_SS_RF_SHUTDOWN;
	else {
		BUG();
		return -EINVAL;	/* shut gcc warnings on certain arches */
	}
}