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
 int /*<<< orphan*/  DIR_OUT ; 
 int /*<<< orphan*/  usbhsp_pipe_cfg_set (struct usbhs_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void usbhs_dcp_dir_for_host(struct usbhs_pipe *pipe, int dir_out)
{
	usbhsp_pipe_cfg_set(pipe, DIR_OUT,
			    dir_out ? DIR_OUT : 0);
}