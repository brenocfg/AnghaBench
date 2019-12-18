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
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int TRCLR ; 
 int TRENB ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_BULK ; 
 int usbhs_pipe_get_maxpacket (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_is_dir_in (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_type_is (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsp_pipe_tre_set (struct usbhs_pipe*,int,int) ; 
 int /*<<< orphan*/  usbhsp_pipe_trn_set (struct usbhs_pipe*,int,int /*<<< orphan*/ ) ; 

void usbhs_pipe_set_trans_count_if_bulk(struct usbhs_pipe *pipe, int len)
{
	if (!usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_BULK))
		return;

	/*
	 * clear and disable transfer counter for IN/OUT pipe
	 */
	usbhsp_pipe_tre_set(pipe, TRCLR | TRENB, TRCLR);

	/*
	 * Only IN direction bulk pipe can use transfer count.
	 * Without using this function,
	 * received data will break if it was large data size.
	 * see PIPEnTRN/PIPEnTRE for detail
	 */
	if (usbhs_pipe_is_dir_in(pipe)) {
		int maxp = usbhs_pipe_get_maxpacket(pipe);

		usbhsp_pipe_trn_set(pipe, 0xffff, DIV_ROUND_UP(len, maxp));
		usbhsp_pipe_tre_set(pipe, TRENB, TRENB); /* enable */
	}
}