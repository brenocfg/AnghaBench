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
typedef  int /*<<< orphan*/  u16 ;
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPEBUF ; 
 int /*<<< orphan*/  __usbhsp_pipe_xxx_set (struct usbhs_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usbhs_pipe_is_dcp (struct usbhs_pipe*) ; 

__attribute__((used)) static void usbhsp_pipe_buf_set(struct usbhs_pipe *pipe, u16 mask, u16 val)
{
	if (usbhs_pipe_is_dcp(pipe))
		return;

	__usbhsp_pipe_xxx_set(pipe, 0, PIPEBUF, mask, val);
}