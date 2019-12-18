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
struct et8ek8_sensor {int dummy; } ;

/* Variables and functions */
 int et8ek8_power_off (struct et8ek8_sensor*) ; 
 int et8ek8_power_on (struct et8ek8_sensor*) ; 

__attribute__((used)) static int __et8ek8_set_power(struct et8ek8_sensor *sensor, bool on)
{
	return on ? et8ek8_power_on(sensor) : et8ek8_power_off(sensor);
}