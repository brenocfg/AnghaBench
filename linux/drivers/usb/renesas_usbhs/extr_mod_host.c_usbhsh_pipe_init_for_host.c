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
typedef  struct usbhs_pipe* usbhsh_hpriv_to_dcp ;
struct usbhsh_hpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int /*<<< orphan*/ * mod_private; } ;
struct renesas_usbhs_driver_pipe_config {int type; } ;

/* Variables and functions */
 int USB_ENDPOINT_XFER_CONTROL ; 
 struct renesas_usbhs_driver_pipe_config* pipe_configs ; 
 int pipe_size ; 
 struct usbhs_pipe* usbhs_dcp_malloc (struct usbhs_priv*) ; 
 struct renesas_usbhs_driver_pipe_config* usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 struct usbhs_pipe* usbhs_pipe_malloc (struct usbhs_priv*,int,int) ; 
 struct usbhsh_hpriv* usbhsh_priv_to_hpriv (struct usbhs_priv*) ; 

__attribute__((used)) static void usbhsh_pipe_init_for_host(struct usbhs_priv *priv)
{
	struct usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	struct usbhs_pipe *pipe;
	struct renesas_usbhs_driver_pipe_config *pipe_configs =
					usbhs_get_dparam(priv, pipe_configs);
	int pipe_size = usbhs_get_dparam(priv, pipe_size);
	int old_type, dir_in, i;

	/* init all pipe */
	old_type = USB_ENDPOINT_XFER_CONTROL;
	for (i = 0; i < pipe_size; i++) {

		/*
		 * data "output" will be finished as soon as possible,
		 * but there is no guaranty at data "input" case.
		 *
		 * "input" needs "standby" pipe.
		 * So, "input" direction pipe > "output" direction pipe
		 * is good idea.
		 *
		 * 1st USB_ENDPOINT_XFER_xxx will be output direction,
		 * and the other will be input direction here.
		 *
		 * ex)
		 * ...
		 * USB_ENDPOINT_XFER_ISOC -> dir out
		 * USB_ENDPOINT_XFER_ISOC -> dir in
		 * USB_ENDPOINT_XFER_BULK -> dir out
		 * USB_ENDPOINT_XFER_BULK -> dir in
		 * USB_ENDPOINT_XFER_BULK -> dir in
		 * ...
		 */
		dir_in = (pipe_configs[i].type == old_type);
		old_type = pipe_configs[i].type;

		if (USB_ENDPOINT_XFER_CONTROL == pipe_configs[i].type) {
			pipe = usbhs_dcp_malloc(priv);
			usbhsh_hpriv_to_dcp(hpriv) = pipe;
		} else {
			pipe = usbhs_pipe_malloc(priv,
						 pipe_configs[i].type,
						 dir_in);
		}

		pipe->mod_private = NULL;
	}
}