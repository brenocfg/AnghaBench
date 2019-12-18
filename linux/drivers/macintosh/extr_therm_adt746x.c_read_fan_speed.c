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
typedef  int u8 ;
typedef  int u16 ;
struct thermostat {int dummy; } ;

/* Variables and functions */
 int read_reg (struct thermostat*,int) ; 

__attribute__((used)) static int read_fan_speed(struct thermostat *th, u8 addr)
{
	u8 tmp[2];
	u16 res;
	
	/* should start with low byte */
	tmp[1] = read_reg(th, addr);
	tmp[0] = read_reg(th, addr + 1);
	
	res = tmp[1] + (tmp[0] << 8);
	/* "a value of 0xffff means that the fan has stopped" */
	return (res == 0xffff ? 0 : (90000*60)/res);
}