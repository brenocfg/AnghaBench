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
struct tda8083_state {int dummy; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;

/* Variables and functions */
 int EINVAL ; 
#define  SEC_VOLTAGE_13 129 
#define  SEC_VOLTAGE_18 128 
 int tda8083_writereg (struct tda8083_state*,int,int) ; 

__attribute__((used)) static int tda8083_set_voltage(struct tda8083_state *state,
			       enum fe_sec_voltage voltage)
{
	switch (voltage) {
	case SEC_VOLTAGE_13:
		return tda8083_writereg (state, 0x20, 0x00);
	case SEC_VOLTAGE_18:
		return tda8083_writereg (state, 0x20, 0x11);
	default:
		return -EINVAL;
	}
}