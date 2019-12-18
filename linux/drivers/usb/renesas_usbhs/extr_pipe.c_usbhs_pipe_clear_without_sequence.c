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
 int /*<<< orphan*/  BFRE ; 
 int /*<<< orphan*/  usbhs_pipe_clear (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_data_sequence (struct usbhs_pipe*,int) ; 
 int usbhs_pipe_get_data_sequence (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsp_pipe_cfg_set (struct usbhs_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsp_pipe_select (struct usbhs_pipe*) ; 

void usbhs_pipe_clear_without_sequence(struct usbhs_pipe *pipe,
				       int needs_bfre, int bfre_enable)
{
	int sequence;

	usbhsp_pipe_select(pipe);
	sequence = usbhs_pipe_get_data_sequence(pipe);
	if (needs_bfre)
		usbhsp_pipe_cfg_set(pipe, BFRE, bfre_enable ? BFRE : 0);
	usbhs_pipe_clear(pipe);
	usbhs_pipe_data_sequence(pipe, sequence);
}