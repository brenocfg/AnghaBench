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
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_CONTROL ; 
 struct usbhs_pipe* usbhsp_get_pipe (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

struct usbhs_pipe *usbhs_dcp_malloc(struct usbhs_priv *priv)
{
	struct usbhs_pipe *pipe;

	pipe = usbhsp_get_pipe(priv, USB_ENDPOINT_XFER_CONTROL);
	if (!pipe)
		return NULL;

	INIT_LIST_HEAD(&pipe->list);

	/*
	 * call usbhs_pipe_config_update() after this function !!
	 */

	return pipe;
}