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
struct can_device_stats {int /*<<< orphan*/  error_passive; int /*<<< orphan*/  error_warning; int /*<<< orphan*/  bus_off; int /*<<< orphan*/  restarts; } ;
struct TYPE_2__ {void* state; struct can_device_stats can_stats; } ;
struct gs_can {TYPE_1__ can; } ;
struct can_frame {int can_id; int* data; } ;

/* Variables and functions */
 int CAN_ERR_BUSOFF ; 
 int CAN_ERR_CRTL ; 
 int CAN_ERR_CRTL_RX_PASSIVE ; 
 int CAN_ERR_CRTL_RX_WARNING ; 
 int CAN_ERR_CRTL_TX_PASSIVE ; 
 int CAN_ERR_CRTL_TX_WARNING ; 
 int CAN_ERR_RESTARTED ; 
 void* CAN_STATE_BUS_OFF ; 
 void* CAN_STATE_ERROR_ACTIVE ; 
 void* CAN_STATE_ERROR_PASSIVE ; 
 void* CAN_STATE_ERROR_WARNING ; 

__attribute__((used)) static void gs_update_state(struct gs_can *dev, struct can_frame *cf)
{
	struct can_device_stats *can_stats = &dev->can.can_stats;

	if (cf->can_id & CAN_ERR_RESTARTED) {
		dev->can.state = CAN_STATE_ERROR_ACTIVE;
		can_stats->restarts++;
	} else if (cf->can_id & CAN_ERR_BUSOFF) {
		dev->can.state = CAN_STATE_BUS_OFF;
		can_stats->bus_off++;
	} else if (cf->can_id & CAN_ERR_CRTL) {
		if ((cf->data[1] & CAN_ERR_CRTL_TX_WARNING) ||
		    (cf->data[1] & CAN_ERR_CRTL_RX_WARNING)) {
			dev->can.state = CAN_STATE_ERROR_WARNING;
			can_stats->error_warning++;
		} else if ((cf->data[1] & CAN_ERR_CRTL_TX_PASSIVE) ||
			   (cf->data[1] & CAN_ERR_CRTL_RX_PASSIVE)) {
			dev->can.state = CAN_STATE_ERROR_PASSIVE;
			can_stats->error_passive++;
		} else {
			dev->can.state = CAN_STATE_ERROR_ACTIVE;
		}
	}
}