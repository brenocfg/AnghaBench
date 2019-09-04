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
struct net_device {int dummy; } ;
struct can_berr_counter {int txerr; int rxerr; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int CAN_STATE_BUS_OFF ; 
 int CAN_STATE_ERROR_ACTIVE ; 
 int CAN_STATE_ERROR_PASSIVE ; 
 int CAN_STATE_ERROR_WARNING ; 
 int at91_get_berr_counter (struct net_device const*,struct can_berr_counter*) ; 

__attribute__((used)) static int at91_get_state_by_bec(const struct net_device *dev,
		enum can_state *state)
{
	struct can_berr_counter bec;
	int err;

	err = at91_get_berr_counter(dev, &bec);
	if (err)
		return err;

	if (bec.txerr < 96 && bec.rxerr < 96)
		*state = CAN_STATE_ERROR_ACTIVE;
	else if (bec.txerr < 128 && bec.rxerr < 128)
		*state = CAN_STATE_ERROR_WARNING;
	else if (bec.txerr < 256 && bec.rxerr < 256)
		*state = CAN_STATE_ERROR_PASSIVE;
	else
		*state = CAN_STATE_BUS_OFF;

	return 0;
}