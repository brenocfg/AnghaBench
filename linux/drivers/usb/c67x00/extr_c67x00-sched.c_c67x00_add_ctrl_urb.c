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
struct urb {int interval; int /*<<< orphan*/  pipe; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  dev; int /*<<< orphan*/ * setup_packet; } ;
struct c67x00_hcd {int dummy; } ;

/* Variables and functions */
#define  DATA_STAGE 130 
#define  SETUP_STAGE 129 
#define  STATUS_STAGE 128 
 int USB_PID_IN ; 
 int USB_PID_OUT ; 
 int USB_PID_SETUP ; 
 int c67x00_add_data_urb (struct c67x00_hcd*,struct urb*) ; 
 int c67x00_create_td (struct c67x00_hcd*,struct urb*,int /*<<< orphan*/ *,int,int,int,int const) ; 
 int /*<<< orphan*/  usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_settoggle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int c67x00_add_ctrl_urb(struct c67x00_hcd *c67x00, struct urb *urb)
{
	int ret;
	int pid;

	switch (urb->interval) {
	default:
	case SETUP_STAGE:
		ret = c67x00_create_td(c67x00, urb, urb->setup_packet,
				       8, USB_PID_SETUP, 0, SETUP_STAGE);
		if (ret)
			return ret;
		urb->interval = SETUP_STAGE;
		usb_settoggle(urb->dev, usb_pipeendpoint(urb->pipe),
			      usb_pipeout(urb->pipe), 1);
		break;
	case DATA_STAGE:
		if (urb->transfer_buffer_length) {
			ret = c67x00_add_data_urb(c67x00, urb);
			if (ret)
				return ret;
			break;
		}		/* else fallthrough */
	case STATUS_STAGE:
		pid = !usb_pipeout(urb->pipe) ? USB_PID_OUT : USB_PID_IN;
		ret = c67x00_create_td(c67x00, urb, NULL, 0, pid, 1,
				       STATUS_STAGE);
		if (ret)
			return ret;
		break;
	}

	return 0;
}