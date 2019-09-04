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
struct cyapa {int dummy; } ;
typedef  int /*<<< orphan*/  ping ;

/* Variables and functions */
 int PIP_DEEP_SLEEP_STATE_ON ; 
 int /*<<< orphan*/  cyapa_i2c_pip_write (struct cyapa*,int*,int) ; 
 int cyapa_pip_deep_sleep (struct cyapa*,int) ; 

__attribute__((used)) static int cyapa_gen6_deep_sleep(struct cyapa *cyapa, u8 state)
{
	u8 ping[] = { 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, 0x00 };

	if (state == PIP_DEEP_SLEEP_STATE_ON)
		/*
		 * Send ping command to notify device prepare for wake up
		 * when it's in deep sleep mode. At this time, device will
		 * response nothing except an I2C NAK.
		 */
		cyapa_i2c_pip_write(cyapa, ping, sizeof(ping));

	return cyapa_pip_deep_sleep(cyapa, state);
}