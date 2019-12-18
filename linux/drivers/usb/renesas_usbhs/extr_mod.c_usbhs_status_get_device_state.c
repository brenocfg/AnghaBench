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
struct usbhs_irq_state {int intsts0; } ;

/* Variables and functions */
#define  ADDRESS_STATE 131 
#define  CONFIGURATION_STATE 130 
#define  DEFAULT_STATE 129 
 int DVSQ_MASK ; 
 int EIO ; 
#define  POWER_STATE 128 

int usbhs_status_get_device_state(struct usbhs_irq_state *irq_state)
{
	int state = irq_state->intsts0 & DVSQ_MASK;

	switch (state) {
	case POWER_STATE:
	case DEFAULT_STATE:
	case ADDRESS_STATE:
	case CONFIGURATION_STATE:
		return state;
	}

	return -EIO;
}