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
 int /*<<< orphan*/  IS_RUNNING ; 
 int /*<<< orphan*/  usbhsp_flags_clr (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsp_flags_set (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 

void usbhs_pipe_running(struct usbhs_pipe *pipe, int running)
{
	if (running)
		usbhsp_flags_set(pipe, IS_RUNNING);
	else
		usbhsp_flags_clr(pipe, IS_RUNNING);
}