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
struct cx231xx {scalar_t__ port_3_switch_enabled; } ;

/* Variables and functions */
 int I2C_1_MUX_1 ; 
 int I2C_1_MUX_3 ; 

__attribute__((used)) static inline int get_real_i2c_port(struct cx231xx *dev, int bus_nr)
{
	if (bus_nr == 1)
		return dev->port_3_switch_enabled ? I2C_1_MUX_3 : I2C_1_MUX_1;
	return bus_nr;
}