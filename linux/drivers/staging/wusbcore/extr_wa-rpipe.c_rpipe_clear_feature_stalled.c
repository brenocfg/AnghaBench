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
typedef  int /*<<< orphan*/  u16 ;
struct wahc {int /*<<< orphan*/  rpipe_mutex; int /*<<< orphan*/  usb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wRPipeIndex; } ;
struct wa_rpipe {TYPE_1__ descr; } ;
struct usb_host_endpoint {struct wa_rpipe* hcpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPIPE_STALL ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_RPIPE ; 
 int /*<<< orphan*/  USB_REQ_CLEAR_FEATURE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rpipe_clear_feature_stalled(struct wahc *wa, struct usb_host_endpoint *ep)
{
	struct wa_rpipe *rpipe;

	mutex_lock(&wa->rpipe_mutex);
	rpipe = ep->hcpriv;
	if (rpipe != NULL) {
		u16 index = le16_to_cpu(rpipe->descr.wRPipeIndex);

		usb_control_msg(
			wa->usb_dev, usb_sndctrlpipe(wa->usb_dev, 0),
			USB_REQ_CLEAR_FEATURE,
			USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_RPIPE,
			RPIPE_STALL, index, NULL, 0, USB_CTRL_SET_TIMEOUT);
	}
	mutex_unlock(&wa->rpipe_mutex);
}