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
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct pvr2_context {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  PVR2_TRACE_INIT ; 
 struct pvr2_context* pvr2_context_create (struct usb_interface*,struct usb_device_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pvr_setup_attach ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct pvr2_context*) ; 

__attribute__((used)) static int pvr_probe(struct usb_interface *intf,
		     const struct usb_device_id *devid)
{
	struct pvr2_context *pvr;

	/* Create underlying hardware interface */
	pvr = pvr2_context_create(intf,devid,pvr_setup_attach);
	if (!pvr) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Failed to create hdw handler");
		return -ENOMEM;
	}

	pvr2_trace(PVR2_TRACE_INIT,"pvr_probe(pvr=%p)",pvr);

	usb_set_intfdata(intf, pvr);

	return 0;
}