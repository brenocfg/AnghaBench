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
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int CAN_ERR_CRTL_ACTIVE ; 
 int CAN_ERR_CRTL_RX_PASSIVE ; 
 int CAN_ERR_CRTL_RX_WARNING ; 
#define  CAN_STATE_ERROR_ACTIVE 130 
#define  CAN_STATE_ERROR_PASSIVE 129 
#define  CAN_STATE_ERROR_WARNING 128 

__attribute__((used)) static int can_rx_state_to_frame(struct net_device *dev, enum can_state state)
{
	switch (state) {
	case CAN_STATE_ERROR_ACTIVE:
		return CAN_ERR_CRTL_ACTIVE;
	case CAN_STATE_ERROR_WARNING:
		return CAN_ERR_CRTL_RX_WARNING;
	case CAN_STATE_ERROR_PASSIVE:
		return CAN_ERR_CRTL_RX_PASSIVE;
	default:
		return 0;
	}
}