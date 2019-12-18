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
struct dwc2_host_chan {scalar_t__ speed; int multi_count; void* data_pid_start; scalar_t__ ep_is_in; } ;

/* Variables and functions */
 void* DWC2_HC_PID_DATA0 ; 
 void* DWC2_HC_PID_DATA1 ; 
 void* DWC2_HC_PID_DATA2 ; 
 void* DWC2_HC_PID_MDATA ; 
 scalar_t__ USB_SPEED_HIGH ; 

__attribute__((used)) static void dwc2_set_pid_isoc(struct dwc2_host_chan *chan)
{
	/* Set up the initial PID for the transfer */
	if (chan->speed == USB_SPEED_HIGH) {
		if (chan->ep_is_in) {
			if (chan->multi_count == 1)
				chan->data_pid_start = DWC2_HC_PID_DATA0;
			else if (chan->multi_count == 2)
				chan->data_pid_start = DWC2_HC_PID_DATA1;
			else
				chan->data_pid_start = DWC2_HC_PID_DATA2;
		} else {
			if (chan->multi_count == 1)
				chan->data_pid_start = DWC2_HC_PID_DATA0;
			else
				chan->data_pid_start = DWC2_HC_PID_MDATA;
		}
	} else {
		chan->data_pid_start = DWC2_HC_PID_DATA0;
	}
}