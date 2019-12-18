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
struct usbhsg_uep {int dummy; } ;
struct usbhsg_gpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int dummy; } ;
struct usb_ctrlrequest {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBHSG_STATUS_WEDGE ; 
 int /*<<< orphan*/  usbhs_pipe_disable (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_enable (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_sequence_data0 (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pkt_start (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsg_recip_handler_std_control_done (struct usbhs_priv*,struct usbhsg_uep*,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  usbhsg_status_has (struct usbhsg_gpriv*,int /*<<< orphan*/ ) ; 
 struct usbhsg_gpriv* usbhsg_uep_to_gpriv (struct usbhsg_uep*) ; 
 struct usbhs_pipe* usbhsg_uep_to_pipe (struct usbhsg_uep*) ; 

__attribute__((used)) static int usbhsg_recip_handler_std_clear_endpoint(struct usbhs_priv *priv,
						   struct usbhsg_uep *uep,
						   struct usb_ctrlrequest *ctrl)
{
	struct usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	struct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);

	if (!usbhsg_status_has(gpriv, USBHSG_STATUS_WEDGE)) {
		usbhs_pipe_disable(pipe);
		usbhs_pipe_sequence_data0(pipe);
		usbhs_pipe_enable(pipe);
	}

	usbhsg_recip_handler_std_control_done(priv, uep, ctrl);

	usbhs_pkt_start(pipe);

	return 0;
}