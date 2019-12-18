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
typedef  int u16 ;
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 int INBUFM ; 
 scalar_t__ usbhs_pipe_is_dcp (struct usbhs_pipe*) ; 
 int usbhsp_pipectrl_get (struct usbhs_pipe*) ; 

bool usbhs_pipe_contains_transmittable_data(struct usbhs_pipe *pipe)
{
	u16 val;

	/* Do not support for DCP pipe */
	if (usbhs_pipe_is_dcp(pipe))
		return false;

	val = usbhsp_pipectrl_get(pipe);
	if (val & INBUFM)
		return true;

	return false;
}